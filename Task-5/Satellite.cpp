#include "stdafx.h"
#include "Satellite.h"


Satellite::Satellite()
{
	InitializeCountries();
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
