#include "SoundCloudClient.h"
#include "Poco/Net/HTTPResponse.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace Poco::Net;
#define CLIENT_ID "521372fec198e4af7c4df3101b1d3e87"
#define CLIENT_SECRET "854d62ea7b6ff819db9e171f16687bbc"
#define SOUNDCLOUD_API_HOST "api.soundcloud.com"

SoundCloudClient::SoundCloudClient()
{
}



string GetStreamUriByTrackId(int id)
{
	string uri("/tracks/");
    stringstream ss;
    ss << id;
	uri.append(ss.str());
	uri.append("/stream?client_id=");
	uri.append(CLIENT_ID);
	return uri;
}

char buf[4096];

void SoundCloudClient::GetTrack(int id)
{

	HTTPClientSession client1;
	HTTPRequest request1;
	HTTPResponse response1;
	request1.setMethod("GET");
	client1.setHost(SOUNDCLOUD_API_HOST);
	request1.setURI(GetStreamUriByTrackId(123456));
	client1.sendRequest(request1);
	istream* responseStream = &client1.receiveResponse(response1);

	responseStream->getline(buf,4096);
	
	URI streamUri = URI(response1.get("Location"));

	HTTPClientSession client2(streamUri.getHost(),80);
	HTTPRequest request2;
	HTTPResponse response2;
	request2.setMethod("GET");
	request2.setURI(streamUri.getPathAndQuery());

	client2.setHost(streamUri.getHost());

	client2.sendRequest(request2);
	string path = streamUri.getHost();
	path.append(streamUri.getPathAndQuery());
	responseStream = &client2.receiveResponse(response2); 
	ofstream myFile;
	myFile.open("saved.mp3");
	myFile << responseStream->rdbuf();
	myFile.close();

}
