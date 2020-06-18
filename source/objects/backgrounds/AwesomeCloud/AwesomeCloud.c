/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2018 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
void AwesomeCloud::constructor(AwesomeCloudSpec* awesomeCloudSpec, s16 internalId, const char* const name)
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

void AwesomeCloud::update(u32 elapsedTime)
{
	Base::update(this, elapsedTime);
/*
	static s16 increment = 1;

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

