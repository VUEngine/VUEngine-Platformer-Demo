/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <AwesomeCloud.h>
#include <TimerManager.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void AwesomeCloud::constructor(AwesomeCloudSpec* awesomeCloudSpec, int16 internalId, const char* const name)
{
	// construct base
	Base::constructor(&awesomeCloudSpec->entitySpec, internalId, name);

	this->awesomeCloudSpec = awesomeCloudSpec;
}

// class's destructor
void AwesomeCloud::destructor()
{
	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

// ready method
void AwesomeCloud::ready(bool recursive)
{
	// call base
	Base::ready(this, recursive);

	this->transformation.localRotation.x = this->awesomeCloudSpec->rotation;
	
	Entity::setLocalRotation(this, &this->transformation.localRotation);
}

void AwesomeCloud::update(uint32 elapsedTime)
{
	Base::update(this, elapsedTime);
/*
	static int16 increment = 1;

	this->transformation.localRotation.x+=increment;

	if(96 < this->transformation.localRotation.x)
	{
		increment *= -1;
	}
	else if(-96 > this->transformation.localRotation.x)
	{
		increment *= -1;
	}

//	increment *= -1;

	
//	this->transformation.localRotation.x *= -1;
	Entity::setLocalRotation(this, &this->transformation.localRotation);
//	TimerManager::wait(TimerManager::getInstance(), 1000);
*/
}

