#pragma once


#include <vector>
#include <stack>
#include <iostream>
#include "Events.h"
#include <string>


class Command
{

public:
    virtual ~Command(){};
    virtual void execute(gpp::Events* event) = 0;
protected:
    Command(){};
};

class AccendLadderStartCommand : public Command
{
    virtual void execute(gpp::Events* event){event->setCurrent(gpp::Events::Event::ASCEND_LADDER_EVENT);}
};

class AccendLadderStopCommand : public Command
{
    virtual void execute(gpp::Events* event){event->setCurrent(gpp::Events::Event::MOVE_UP_STOP_EVENT);}
};

class AttackStartCommand : public Command
{
    virtual void execute(gpp::Events* event){event->setCurrent(gpp::Events::Event::ATTACK_START_EVENT);}
};

class AttackStopCommand : public Command
{
    virtual void execute(gpp::Events* event){event->setCurrent(gpp::Events::Event::ATTACK_STOP_EVENT);}
};

class ClimbDownStartCommand : public Command
{
    virtual void execute(gpp::Events* event){event->setCurrent(gpp::Events::Event::MOVE_DOWN_START_EVENT);}
};

class ClimbDownStopCommand : public Command
{
    virtual void execute(gpp::Events* event){event->setCurrent(gpp::Events::Event::MOVE_DOWN_STOP_EVENT);}
};

class HitLadderBottomCommand : public Command
{
    virtual void execute(gpp::Events* event){event->setCurrent(gpp::Events::Event::HIT_LADDER_BOTTOM_EVENT);}
};

class HitLadderTopCommand : public Command
{
    virtual void execute(gpp::Events* event){event->setCurrent(gpp::Events::Event::HIT_LADDER_TOP_EVENT);}
};

class HitGroundCommand : public Command
{
    virtual void execute(gpp::Events* event){event->setCurrent(gpp::Events::Event::HIT_GROUND_EVENT);}
};


class DescendLadderCommand : public Command
{
    virtual void execute(gpp::Events* event){event->setCurrent(gpp::Events::Event::DESCEND_LADDER_EVENT);}
};

class DiedCommand : public Command
{
    virtual void execute(gpp::Events* event){event->setCurrent(gpp::Events::Event::DIED_EVENT);}
};

class GlideCommand : public Command
{
    virtual void execute(gpp::Events* event){event->setCurrent(gpp::Events::Event::GLIDE_EVENT);}
};

class IdleCommand : public Command
{
    virtual void execute(gpp::Events* event){event->setCurrent(gpp::Events::Event::NONE);}
};

class JumpAttackStartCommand : public Command
{
    virtual void execute(gpp::Events* event){event->setCurrent(gpp::Events::Event::JUMP_ATTACK_START_EVENT);}
};

class JumpAttackStopCommand : public Command
{
    virtual void execute(gpp::Events* event){event->setCurrent(gpp::Events::Event::JUMP_ATTACK_STOP_EVENT);}
};

class JumpStartCommand : public Command
{
    virtual void execute(gpp::Events* event){event->setCurrent(gpp::Events::Event::JUMP_UP_EVENT);}
};

class JumpThrowStartCommand : public Command
{
    virtual void execute(gpp::Events* event){event->setCurrent(gpp::Events::Event::JUMP_THROW_START_EVENT);}
};

class ReviveCommand : public Command
{
    virtual void execute(gpp::Events* event){event->setCurrent(gpp::Events::Event::REVIVED_EVENT);}
};

class RunRightStartCommand : public Command
{
    virtual void execute(gpp::Events* event){event->setCurrent(gpp::Events::Event::RUN_RIGHT_START_EVENT);}
};

class RunRightStopCommand : public Command
{
    virtual void execute(gpp::Events* event){event->setCurrent(gpp::Events::Event::RUN_RIGHT_STOP_EVENT);}
};

class SlideCommand : public Command
{
    virtual void execute(gpp::Events* event){event->setCurrent(gpp::Events::Event::SLIDE_EVENT);}
};

class ThrowStartCommand : public Command
{
    virtual void execute(gpp::Events* event){event->setCurrent(gpp::Events::Event::THROW_START_EVENT);}
};

class ThrowStopCommand : public Command
{
    virtual void execute(gpp::Events* event){event->setCurrent(gpp::Events::Event::THROW_STOP_EVENT);}
};