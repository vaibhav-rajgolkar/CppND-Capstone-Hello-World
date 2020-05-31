#include "player.h"

void Player::UpdatePlayerPosition() 
{
	if(updatePosition_)
	{
		switch (direction_) 
		{
    		case Direction::kUp:
      			yPosition_ -= speed_;
      			break;

    		case Direction::kDown:
      			yPosition_ += speed_;
      			break;

    		case Direction::kLeft:
      			xPosition_ -= speed_;
      			break;

    		case Direction::kRight:
      			xPosition_ += speed_;
      			break;
  		}
	}
}