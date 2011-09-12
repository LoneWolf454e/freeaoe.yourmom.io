/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2011  <copyright holder> <email>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "Graphic.h"
#include <file/SlpFile.h>
#include <data/DataManager.h>
#include "ResourceManager.h"
#include <file/SlpFrame.h>

namespace res
{

//------------------------------------------------------------------------------
Graphic::Graphic(sf::Uint32 id) : Resource(id, TYPE_GRAPHIC), data_(0)
{

}

//------------------------------------------------------------------------------
Graphic::~Graphic()
{

}

//------------------------------------------------------------------------------
const sf::Image& Graphic::getImage(Uint32 frame_num, bool mirrored)
{
  sf::Image *img = slp_->getFrame(frame_num)->getImage();
  
  if (mirrored)
  {
    img = new sf::Image(*img);
    img->FlipHorizontally();
  }
  
  return *img;
}

//------------------------------------------------------------------------------
ScreenPos Graphic::getHotspot(Uint32 frame_num, bool mirrored) const
{
  SlpFrame *frame = slp_->getFrame(frame_num);
  
  Int32 hot_spot_x = frame->getHotspotX();
  
  if (mirrored)
    hot_spot_x = frame->getImage()->GetWidth() - hot_spot_x;
  
  return ScreenPos(hot_spot_x, frame->getHotspotY());
}

//------------------------------------------------------------------------------
float Graphic::getFrameRate(void ) const
{
  return data_->frame_rate_;
}

//------------------------------------------------------------------------------
Uint32 Graphic::getFrameCount(void ) const
{
  return data_->frame_count_;
}

//------------------------------------------------------------------------------
Uint32 Graphic::getAngleCount(void ) const
{
  return data_->angle_count_;
}

//------------------------------------------------------------------------------
void Graphic::load()
{
  if (data_ == 0)
  {
  data_ = new GenieGraphic(DataManager::Inst()->getGraphic(getId()));
  
  slp_ = ResourceManager::Inst()->getSlp(data_->getSlpId());
  slp_->load();
  
  Resource::load();
  }
}

}