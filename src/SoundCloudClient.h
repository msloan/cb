#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Uri.h"
using namespace std;
using namespace Poco;
using namespace Poco::Net;

class SoundCloudClient 
{

public:

	SoundCloudClient();
	void GetTrack(int id);
	//SoundCloudClient(&URI);
};