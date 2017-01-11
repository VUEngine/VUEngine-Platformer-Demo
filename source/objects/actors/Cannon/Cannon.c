/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2017 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
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
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Game.h>
#include <Entity.h>
#include <MessageDispatcher.h>
#include <Cuboid.h>
#include <PhysicalWorld.h>
#include <ProgressManager.h>
#include <Container.h>
#include <Screen.h>
#include <ParticleSystem.h>
#include <SoundManager.h>

#include <CustomScreenEffectManager.h>
#include <objects.h>
#include <CannonBall.h>
#include "Cannon.h"

#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(Cannon, AnimatedInGameEntity);


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

void Cannon_shoot(Cannon this);
static void Cannon_onCannonBallSpawned(Cannon this, Object eventFirer);

//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(Cannon, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, s16 id, s16 internalId, const char* const name)
__CLASS_NEW_END(Cannon, animatedInGameEntityDefinition, id, internalId, name);

// class's constructor
void Cannon_constructor(Cannon this, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, s16 id, s16 internalId, const char* const name)
{
	ASSERT(this, "Cannon::constructor: null this");

	// construct base
	__CONSTRUCT_BASE(AnimatedInGameEntity, animatedInGameEntityDefinition, id, internalId, name);
}

// class's destructor
void Cannon_destructor(Cannon this)
{
	ASSERT(this, "Cannon::destructor: null this");

    // discard pending delayed messages
    MessageDispatcher_discardDelayedMessagesFromSender(MessageDispatcher_getInstance(), __SAFE_CAST(Object, this), kCannonShoot);

    // not necessary to manually destroy the CannonBall here as all children are automatically
    // destroyed as well when an entity is unloaded

	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

void Cannon_ready(Cannon this, u32 recursive)
{
	ASSERT(this, "Cannon::ready: null this");

	// call base
	AnimatedInGameEntity_ready(__SAFE_CAST(AnimatedInGameEntity, this), recursive);

    // send delayed message to self to trigger first shot
    MessageDispatcher_dispatchMessage(CANNON_INITIAL_SHOOT_DELAY * 4, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kCannonShoot, NULL);
}

// state's handle message
bool Cannon_handleMessage(Cannon this, Telegram telegram)
{
	ASSERT(this, "Cannon::handleMessage: null this");

	switch(Telegram_getMessage(telegram))
    {
		case kCannonShoot:

            Cannon_shoot(this);
			break;
	}

	return false;
}

// start shooting a cannon ball
void Cannon_shoot(Cannon this)
{
	ASSERT(this, "Cannon::shoot: null this");

	if(!this->children)
	{
	    // add cannon ball as child
	    extern PositionedEntityROMDef CANNON_BALL;

        Stage_spawnEntity(Game_getStage(Game_getInstance()), &CANNON_BALL, __SAFE_CAST(Container, this), (EventListener)Cannon_onCannonBallSpawned);
        return;
	}

    // start shooting sequence
	AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, this), "Shoot");

    // send delayed message to self to trigger next shot
    MessageDispatcher_dispatchMessage(CANNON_SHOOT_DELAY, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kCannonShoot, NULL);
}

static void Cannon_onCannonBallSpawned(Cannon this, Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "Cannon::onCannonBallSpawned: null this");

    // start shooting sequence
	AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, this), "Shoot");

    // send delayed message to self to trigger next shot
    MessageDispatcher_dispatchMessage(CANNON_SHOOT_DELAY, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kCannonShoot, NULL);
}

// spawn a cannon ball, this is the callback of the "Shoot" animation
void Cannon_spawnCannonBall(Cannon this)
{
	ASSERT(this, "Cannon::spawnCannonBall: null this");

    // start short screen shake
    Screen_startEffect(Screen_getInstance(), kShake, 250);

    // play boom sound
    extern const u16 FIRE_SND[];
    SoundManager_playFxSound(SoundManager_getInstance(), FIRE_SND, this->transform.globalPosition);

    // set cannon ball to moving state
    ASSERT(1 == VirtualList_getSize(this->children), "Cannon::spawnCannonBall: no children");
    CannonBall cannonBall = __SAFE_CAST(CannonBall, VirtualList_front(this->children));

    MessageDispatcher_dispatchMessage(1, __SAFE_CAST(Object, this), __SAFE_CAST(Object, cannonBall), kCannonShoot, NULL);
}
