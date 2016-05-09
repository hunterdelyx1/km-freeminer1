local object = {
	name = "server_connect",
	type = "toplevel"
}

object.hide = function(self)
	self.hidden = true
end

object.show = function(self)
	self.hidden = false
end

object.delete = function(self)
    ui.delete(self)
end

object.handle_buttons = function(self, fields)
	if (fields.main_connect_button or fields.key_enter) and
       (fields.login_field and fields.password_field) then
       
		gamedata.playername = fields.login_field
		gamedata.password   = fields.password_field
        
		gamedata.address    = "127.0.0.1"
		gamedata.port       = "30000"

		core.setting_set("address",     gamedata.address)
		core.setting_set("remote_port", gamedata.port)

		core.start()
		return true
	end
end

object.handle_events = function(self, event)
    print(event)
end

object.get_formspec = function(self)
	return "size[6,5,".. dump(true) .. "]"..
            "field[1,1;4,1;login_field;login;]"..
            "pwdfield[1,2.5;4,1;password_field;password;]"..
            "button[0.8,4;4,1;main_connect_button;connect]" .. 
            "background[-50,-50;100,100;" .. core.formspec_escape(defaulttexturedir .. "background.png") .. "]"
end

return object
