#include "stdafx.h"
#include "Satellite.h"
#include <iostream>


Satellite::Satellite()
{
	for (int i = 0; i < Country::CountryName::COUNT; i++)
	{
		Country* c = new Country;
		c->name = (Country::CountryName)i;
		c->terabytePackage = Random::RandomInt(1, 5);
		// Check this out:
		c->activated = (Random::RandomInt(0, 2) ? 1 : 0);

		if (c->activated)
		{
			countryQueue.queuedCountries.push_back(c);
		}
		else countryQueue.satisfiedCountries.push_back(c);
	}
	std::random_shuffle(countryQueue.queuedCountries.begin(), countryQueue.queuedCountries.end());

	if (!countryQueue.queuedCountries.empty())
	{
		channels[0].country = countryQueue.queuedCountries.back();
		channels[0].empty = false;
		countryQueue.queuedCountries.pop_back();
	}
	if (!countryQueue.queuedCountries.empty())
	{
		channels[1].country = countryQueue.queuedCountries.back();
		channels[1].empty = false;
		countryQueue.queuedCountries.pop_back();
	}
	Broadcast();
}

Satellite::~Satellite()
{
}

void Satellite::Broadcast()
{
	while (!channels[0].empty || !channels[1].empty)
	{
		ProcessChannel(0);
		ProcessChannel(1);
	}
	DownForMaintenence();

	std::cout << "Total profit: $" << totalProfit;
}

void Satellite::ProcessChannel(int whichChannel)
{
	// Take in int for which channel to process
	// That channel will transmit data for a based on terabytePackage for the given TransmissionTime()
	// Add TransmissionPrice() to totalProfit in satellite
	// add to maintenenceDuration the amount of TransmissionTime()
	// Move the channel's country into satisifedCountries vector in countryQueue

	if (!channels[whichChannel].empty)
	{
		// Have not reached end of transmission time
		if (channels[whichChannel].country->currentTransmissionAmount < channels[whichChannel].country->TransmissionTime())
		{
			totalProfit = totalProfit + channels[whichChannel].country->transmissionPrice();
			channels[whichChannel].country->currentTransmissionAmount++;
			maintenanceDuration++;

		}

		// Reached end of transmission time
		if (channels[whichChannel].country->currentTransmissionAmount == channels[whichChannel].country->TransmissionTime())
		{
			countryQueue.satisfiedCountries.push_back(channels[whichChannel].country);

			if (!countryQueue.queuedCountries.empty())
			{
				channels[whichChannel].country = countryQueue.queuedCountries.back();
				countryQueue.queuedCountries.pop_back();
				channels[whichChannel].empty = false;
			}
			else channels[whichChannel].empty = true;
		}
	}
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
