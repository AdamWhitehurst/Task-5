#pragma once
#include <cstdlib>
#include <vector>
#include <algorithm>

class Random
{
public:
	// Generates uniform distribution between rangeLow and rangeHigh, exclusive
	static int RandomInt(int rangeLow, int rangeHigh) {
		double myRand = rand() / (1.0 + RAND_MAX);
		int range = rangeHigh - rangeLow;
		int myRand_scaled = (myRand * range) + rangeLow;
		return myRand_scaled;
	}
};

struct Country
{
	enum CountryName { USA, China, Germany, Japan, Switzerland, COUNT } name;
	int terabytePackage;
	int transmissionPrice();
	bool activated;
	int TransmissionTime();
	int currentTransmissionAmount;
};
class Satellite
{
public:
	Satellite();
	~Satellite();
	void InitializeCountries();
	void Broadcast();
	void ProcessChannel(int);

	struct Channel
	{
		Country* country;
	} channels[2];

	struct CountryQueue
	{
		std::vector<Country*>
			queuedCountries,
			satisfiedCountries;
	} countryQueue;
	
	unsigned int totalProfit, maintenanceDuration;

};

