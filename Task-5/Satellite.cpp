#include "stdafx.h"
#include "Satellite.h"
#include <iostream>


Satellite::Satellite()
{
	InitializeCountries();
	Broadcast();
}


Satellite::~Satellite()
{
}

void Satellite::InitializeCountries()
{
	for (int i = 0; i < Country::CountryName::COUNT; i++)
	{
		Country c;
		c.name = (Country::CountryName)i;
		c.terabytePackage = Random::RandomInt(1, 5);
		// Check this out:
		c.activated = (Random::RandomInt(0, 2) ? 1 : 0);

		if (c.activated)
		{
			countryQueue.queuedCountries.push_back(&c);
		} else countryQueue.satisfiedCountries.push_back(&c);
	}
	std::random_shuffle(countryQueue.queuedCountries.begin(), countryQueue.queuedCountries.end());
}

void Satellite::Broadcast()
{
	while (!channels[0].empty || !channels[1].empty)
	{
		ProcessChannel(0);
		ProcessChannel(1);
	}
	DownForMaintenence();

	std::cout << "Total profit: " << totalProfit;
}

void Satellite::ProcessChannel(int)
{
	// Take in int for which cannel to process
	// That channel will transmit data for a based on terabytePackage for the given TransmissionTime()
	// Add TransmissionPrice() to totalProfit in satellite
	// add to maintenenceDuration the amount of TransmissionTime()
	// Move the channel's country into satisifedCountries vector in countryQueue

}

void Satellite::DownForMaintenence()
{
}

int Country::transmissionPrice()
{
	switch (terabytePackage)
	{
	default:
	case 1:
		return 210;
	case 2:
		return 350;
	case 3:
		return 400;
	case 4:
		return 500;
	}
}

int Country::TransmissionTime()
{
	switch (terabytePackage)
	{
	default:
	case 1:
		return 1;
	case 2:
		return 3;
	case 3:
		return 5;
	case 4:
		return 10;
	}
}
