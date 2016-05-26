#include <string>
#include <iostream>

using namespace std;

class LogicalParser {
public:
	string s;
	bool ofstring(char c) {
		return c == '1';
	}
	string tostring(bool a) {
		return a ? "1" : "0";
	}
	bool calc(string s) {
		size_t result;
		while (true) {
			if ((result = s.rfind("-")) != string::npos) {
				bool neg = !ofstring(s.at(result + 1));
				s.replace(result, 2, tostring(neg));
				continue;
			} else if ((result = s.find("|")) != string::npos) {
				bool sh = !(ofstring(s.at(result - 1)) & ofstring(s.at(result + 1)));
				s.replace(result - 1, 3, tostring(sh));
				continue;
			} else if ((result = s.find("^")) != string::npos) {
				bool con = ofstring(s.at(result - 1)) & ofstring(s.at(result + 1));
				s.replace(result - 1, 3, tostring(con));
				continue;
			} else if ((result = s.find("v")) != string::npos) {
				bool dis = ofstring(s.at(result - 1)) | ofstring(s.at(result + 1));
				s.replace(result - 1, 3, tostring(dis));
				continue;
			} else
				break;
		}
		return ofstring(s[0]);
	}
	bool parse(string s) {
		auto open_bracket = s.rfind("(");
		if (open_bracket != string::npos) {
			auto close_bracket = s.find(")", open_bracket);
			bool result = calc(s.substr(open_bracket + 1, close_bracket - open_bracket - 1));
			s.replace(open_bracket, close_bracket - open_bracket + 1, tostring(result));
			return parse(s);
		}
		return calc(s);
	}
	bool process() {
		return parse(s);
	}
};

int main() {
	LogicalParser lp;
	string s;
	getline(cin, s);
	string ss = "";
	for (int i = 0; i < s.length(); i++)
		if (s[i] != ' ')
			ss.push_back(s[i]);
	lp.s = ss;
	cout << lp.process() << endl;
//	system("pause");
	return 0;
}