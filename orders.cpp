#include <iostream>
#include <string>
#include <cassert>
#include <locale>
using namespace std;

//this function return true if string contains valid uppercase statecode
bool isValidUppercaseStateCode(string stateCode)
{
	const string codes =
		"AL.AK.AZ.AR.CA.CO.CT.DE.DC.FL.GA.HI.ID.IL.IN.IA.KS."
		"KY.LA.ME.MD.MA.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC."
		"ND.OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
	return (stateCode.size() == 2 &&
		stateCode.find('.') == string::npos &&  // no '.' in stateCode
		codes.find(stateCode) != string::npos);  // match found
}


//this function extracts the number of orders from each state and totals up the number of cases
int CountOrders(string digitsinStr) {
	string Order = "";
	int TotalCases = 0;
	int i = 0;

	while (i < digitsinStr.size()) {
		while (isdigit(digitsinStr.at(i))) { //while index is a digit                                                                                                                                                                                            en the 
			Order += digitsinStr.at(i); //add digit to Order string
			i++;
		};

		int Stateorder = stoi(Order); //change Order string into int using buildin function
		TotalCases += Stateorder; //total up the individual stateorders 

		Order = ""; //clear both Order string and set Stateorder back to zero for the next stateorder
		Stateorder = 0;
		i++; //increment i to move on to next state
	}

	return TotalCases;
}


//this function tests if the string orders satisfies all the requirements for correct syntax
bool hasValidSyntax(string orders) {
	string Statecode = "";

	if (orders == "") { return true; } //since empty string is correct syntax, set it as true
	int i = 0;
	while (i < orders.size()) {
		while (isalpha(orders.at(i))) {
			Statecode += toupper(orders.at(i)); //capitalize all the alphabets in string order
			i++;
			if (i == orders.size())
				break;
		}
		if (!isValidUppercaseStateCode(Statecode)) { return false; } //if the capitalized alphabets do not form a statecode return false

		Statecode = "";  //clear the string to loop back up for next state

		if (!isdigit(orders.at(i))) { return false; }
		while (isdigit(orders.at(i))) { //check the string for digits that come after statecode
			i++;
			if (i == orders.size())
				break;
		}

		if (i == orders.size())
			break;
		if (orders.at(i) != '+' && orders.at(i) != '-') //check for +/- that comes after digits
		{
			return false;
		}
		i++;
	}
	return true; // if string passes all tests above, then the syntax is valid
}



//this function takes in 3 inputs, counts the  number of positive and negative cases, and return codes 1/2/3/0 depending on the scenarios
int countCases(string orders, char status, int& caseCount) {
	string numOrders = "";
	string PosOrders = "";
	string NegOrders = "";
	int i = 0;

	if (!hasValidSyntax(orders)) //if syntax is not valid, return 1
		return 1;

	while (i < orders.length()) { //goes through similar loop as hasValidSyntax function to get numOrders
		i += 2; //add 2 to skip over the statecode
		while (isdigit(orders.at(i))) {
			numOrders += orders.at(i);
			i++;
		}

		if (stoi(numOrders) == 0) //if any of the number of orders is 0, return 2
			return 2;

		//if digit is followed by +/-, count the orders depending on whether it's +/-
		if (orders.at(i) == '+')
		{
			PosOrders += numOrders + "+";
		}

		if (orders.at(i) == '-')
		{
			NegOrders += numOrders + "-";
		}

		numOrders = ""; //sets numOrders back to 0 again
		i++;
	}
	if (status != '+' && status != '-')  //if status is not +/-, return 3
	{
		return 3;
	}

	//if string does not meet above conditions, then total the number of order in positive and negative
	if (status == '+') {
		caseCount = CountOrders(PosOrders); //sets caseCount to the total number of cases of masks for the state orders in orders that have the status indicated by the status parameter
		return 0;
	}
	if (status == '-') {
		caseCount = CountOrders(NegOrders);
		return 0;
	}
}

int main()
{
	//assert(hasValidSyntax("TX38-CA132+"));
	//assert(!hasValidSyntax("MX38-CA132+"));
	int cases;
	//cases = -999;    // so we can detect whether countCases sets cases
	//assert(countCases("TX38-CA132+Ms6-nY290-UT006+MS8+CA15+", '+', cases) == 0 && cases == 161);
	cases = -999;    // so we can detect whether countCases leaves cases unchanged
	cout << (countCases("TX003+CA132+", '+', cases)) << endl;
	cout << cases << endl;
	//cout << "All tests succeeded" << endl;
}