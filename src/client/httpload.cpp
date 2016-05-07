#include "httpfetch.h"

//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <sys/stat.h>
//#include <sys/types.h>

//std::string getFileModifyTime(std::string path)
//{
	//std::string date = "";
//#ifdef _WIN32
		
//#else
    //// std::locale::global(std::locale("ja_JP.utf8"));
    	
	//struct stat attributes;
	
	//stat(path.c_str(), &attributes);
	//// ctime(&attributes.st_mtime)
	
	//std::stringstream ss;
    //ss << std::put_time(std::gmtime(&attributes.st_mtime), "%a, %d %b %Y %H:%M:%S %Z");
    //return ss.str();
//#endif
	//return date;
//}

namespace httpload
{	
	std::string getCachePath()
	{
		return porting::path_share + DIR_DELIM + "cache" + DIR_DELIM + "httpload";
	}
	
	void saveRemoteImgToFile(const std::string &name, video::IImage* img, IrrlichtDevice *device)
	{
		video::IVideoDriver* driver = device->getVideoDriver();
		
		#ifdef __ANDROID__
			if (!fs::PathExists(httpload::getCachePath())) {
				fs::CreateDir(httpload::getCachePath());
			}
		#else
			fs::CreateDir(httpload::getCachePath());
		#endif
		
		driver->writeImageToFile(img, (httpload::getCachePath() + DIR_DELIM + std::string(name)).c_str());
	}
	
	video::IImage* dataToImage(std::string data, IrrlichtDevice *device)
	{
		video::IVideoDriver* driver = device->getVideoDriver();

		Buffer<char> data_rw(data.c_str(), data.size());
		
		io::IReadFile *rfile = device->getFileSystem()->createMemoryReadFile(
			*data_rw, data_rw.getSize(), "_tempreadfile");
			
		if (!rfile) {
			return NULL;
		}
				
		video::IImage* img = driver->createImageFromFile(rfile);
		
		if (!img) {
            rfile->drop();
			return NULL;
		}
		
		return img;
	}

	video::IImage* getOrLoad(const std::string &name, video::IImage* img_cache, IrrlichtDevice *device)
	{
		if(!str_starts_with(name, "httpload:"))
		{
			return img_cache;
		}
		
		if(g_settings->get("http_get_host") == "")
		{
			errorstream << "Client: No \"http_get_host\" in freeminer.conf " << std::endl;
			return img_cache;
		}
        
		Strfnd sf(name); sf.next(":"); 
		std::string filename = sf.next(":");
		
		std::string url = g_settings->get("http_get_host") + filename;
				
		video::IImage *img_remote = NULL;
				
		// http-request
		HTTPFetchRequest fetch_request;
		fetch_request.url = url;
		fetch_request.caller = HTTPFETCH_SYNC;
		
		//if (path != "" && img) 
		//{
			//std::string date = getFileModifyTime(path);
			//std::cout << std::string("If-Modified-Since: ") + date << std::endl;
			//fetch_request.extra_headers.push_back(std::string("If-Modified-Since: ") + date);
		//}
		
		fetch_request.timeout = g_settings->getS32("curl_file_download_timeout");
		
		// http-response
		HTTPFetchResult fetch_result;
		
		// Activate synchronized http-request
		httpfetch_sync(fetch_request, fetch_result);
        		
		if (!fetch_result.succeeded)
		{
			errorstream << "Client[httpload]: Unable to fetch successfully, url:"<< url << std::endl;
			return img_cache;
		}
		
        if (fetch_result.response_code == 200) // 200: File is modified or new, already downloaded.
		{
			// Convert fetched data to IImage
			img_remote = httpload::dataToImage(fetch_result.data, device);
			
			if (!img_remote)
			{
				errorstream << "Client[httpload]: Cannot create image from data, url: "<< url << std::endl;	
				return img_cache;
			}

			httpload::saveRemoteImgToFile(name, img_remote, device);
			
			return img_remote;
		}
		else if (fetch_result.response_code == 304) // 304: Cached file is ok, no need to download.
		{
			infostream << "Client[httpload]: local cache is valid, keeping it, url: "<< url << std::endl;
		}
		else
		{
			errorstream << "Client[httpload]: response code: " << fetch_result.response_code << ", url: " << url << std::endl;
		}
		
		return img_cache;
	}
}
