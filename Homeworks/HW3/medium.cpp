//#include <iostream>
//#include <string>
//using namespace std;
//
//enum CallType {
//	VOICE, TEXT
//};
//
//Your declarations and implementations would go here
class Medium
{
public:
	Medium(string id) :m_id(id) {};
	virtual ~Medium() {};
	virtual string connect() const = 0;
	virtual string transmit(string msg) const;
	string id() const { return m_id; };
private:
	string m_id;
	string m_connect;
};

string Medium::transmit(string msg) const
{
	string s = "text: ";
	return s + msg;
}

class Phone : public Medium
{
public:
	Phone(string id, CallType type) :Medium(id), m_type(type){};
	virtual ~Phone() { cout << "Destroying the phone " << id() << "." << endl; };
	virtual string connect() const { return "Call"; };
	string transmit(string msg) const;
private:
	CallType m_type;
};

string Phone::transmit(string msg) const
{
	if (m_type == CallType::TEXT)
		return Medium::transmit(msg);
	else
	{
		string s = "voice: ";
		return s + msg;
	}
}

class EmailAccount : public Medium
{
public:
	EmailAccount(string id) : Medium(id) {};
	virtual ~EmailAccount() { cout << "Destroying the email account " << id() << "." << endl; };
	virtual string connect() const { return "Email"; };
private:
};


class TwitterAccount : public Medium
{
public:
	TwitterAccount(string id) :Medium(id) {};
	virtual ~TwitterAccount() { cout << "Destroying the Twitter account " << id() << "." << endl; };
	virtual string connect() const { return "Tweet"; };
private:
};


//void send(const Medium* m, string msg)
//{
//	cout << m->connect() << " using id " << m->id()
//		<< ", sending " << m->transmit(msg) << endl;
//}
//
//int main()
//{
//	Medium* media[4];
//	media[0] = new TwitterAccount("UCLABruinAlert");
//	// Phone users may prefer messages to be left as voice or text.
//	media[1] = new Phone("(310) 825 3894", VOICE);
//	media[2] = new Phone("(213) 389 9060", TEXT);
//	media[3] = new EmailAccount("jbroon@ucla.edu");
//
//	cout << "Send the message." << endl;
//	for (int k = 0; k < 4; k++)
//		send(media[k], "Major power outage in West L.A.");
//
//	// Clean up the media before exiting
//	cout << "Cleaning up." << endl;
//	for (int k = 0; k < 4; k++)
//		delete media[k];
//}