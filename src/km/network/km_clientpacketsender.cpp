void Client::sendChatOpened(bool opened)
{
    MSGPACK_PACKET_INIT(TOSERVER_IS_CHAT_OPENED, 1);
	PACK(TOSERVER_IS_OPENED, opened);

	Send(0, buffer, true);
    return;
}
