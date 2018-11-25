

class LineCollection
{
      // has pairs (line number - line)
      bool hasLine(int lineNumber);
      void setLine(int lineNumber, string line);
      //<sortedCollection> getLines();
};
class OwnedLine
{

};
class LineSharingServer
{
	// when is started, waits on certain port and answers requests, with data from owned line
};
class LineCollectorClient
{
	// scans certain IP range, on certain port range, when there is server and has line we don't have yet (check with LineCollection) then collects it and sends to LineCollection.
};

class LineSharingServersManager
{
	// creates and deletes servers, has collection of them
};

class LineSharingClientManager
{
	// creates and deletes clients, has collection of them
};

class Config
{
	// port range
        // line that has to be shared
};

class Log
{
	// history of established connections: ip, port
        // of send responses
        // of received responses
        // of send requests
        // of received requests
};

