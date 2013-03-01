/* -*- c++ -*- */
/*
 * Copyright 2012 Free Software Foundation, Inc.
 * 
 * This file is part of GNU Radio
 * 
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

/*******************************************************************************
* Copyright 2011 Johns Hopkins University Applied Physics Lab
* Author: Mark Plett 
* Description:
*   The gr_log module wraps the log4cxx library for logging in gnuradio.
*******************************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h" 
#endif

#include <gr_log.h>
#include <stdexcept>
#include <algorithm>

#ifdef ENABLE_GR_LOG

void
logger_load_config(const std::string &config_filename)
{
  if(config_filename.size() == 0) {
    log4cxx::BasicConfigurator::configure();
  }
  else if(config_filename.find(".xml") != std::string::npos) {
    log4cxx::xml::DOMConfigurator::configure(config_filename);
  }
  else {
    log4cxx::PropertyConfigurator::configure(config_filename);
  }
}

void
logger_set_level(log4cxx::LoggerPtr logger, const std::string &level)
{
  std::string nocase = level;
  std::transform(level.begin(), level.end(), nocase.begin(), ::tolower);
  
  if(nocase == "off")
    logger_set_level(logger, log4cxx::Level::getOff());
  else if(nocase == "all")
    logger_set_level(logger, log4cxx::Level::getAll());
  else if(nocase == "trace")
    logger_set_level(logger, log4cxx::Level::getTrace());
  else if(nocase == "debug")
    logger_set_level(logger, log4cxx::Level::getDebug());
  else if(nocase == "info")
    logger_set_level(logger, log4cxx::Level::getInfo());
  else if(nocase == "warn")
    logger_set_level(logger, log4cxx::Level::getWarn());
  else if(nocase == "error")
    logger_set_level(logger, log4cxx::Level::getError());
  else if(nocase == "fatal")
    logger_set_level(logger, log4cxx::Level::getFatal());
  else
    throw std::runtime_error("logger_set_level: Bad level type.\n");
}

void
logger_set_level(log4cxx::LoggerPtr logger, log4cxx::LevelPtr level)
{
  logger->setLevel(level);
}

void 
logger_get_level(log4cxx::LoggerPtr logger,std::string &level)
{
  log4cxx::LevelPtr levelPtr = logger->getLevel();
  if(levelPtr == log4cxx::Level::getOff()) level = "off";
  if(levelPtr == log4cxx::Level::getAll()) level = "all";
  if(levelPtr == log4cxx::Level::getTrace()) level = "trace";
  if(levelPtr == log4cxx::Level::getDebug()) level = "debug";
  if(levelPtr == log4cxx::Level::getInfo()) level = "info";
  if(levelPtr == log4cxx::Level::getWarn()) level = "warn";
  if(levelPtr == log4cxx::Level::getError()) level = "error";
  if(levelPtr == log4cxx::Level::getFatal()) level = "fatal";
};

void 
logger_get_level(log4cxx::LoggerPtr logger,log4cxx::LevelPtr level)
{
  level = logger->getLevel();
}

#endif /* ENABLE_GR_LOG */
