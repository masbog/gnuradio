/* -*- c++ -*- */
/*
 * Copyright 2004 Free Software Foundation, Inc.
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

/*
 * config.h is generated by configure.  It contains the results
 * of probing for features, options etc.  It should be the first
 * file included in your .cc file.
 */

/************************************************
* Johns Hopkins University Applied Physics Lab
* Author: Mark Plett  (Adapted from gr_how_t0_write_a_block_3.2
* Description:
*   This block is a pass through to exercise the logging module gr.error_logger.
**************************************************/

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
    BasicConfigurator::configure();
  }
  else if(config_filename.find(".xml") != std::string::npos) {
    DOMConfigurator::configure(config_filename);
  }
  else {
    PropertyConfigurator::configure(config_filename);
  }
}

void
logger_set_level(LoggerPtr logger, const std::string &level)
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
logger_set_level(LoggerPtr logger, log4cxx::LevelPtr level)
{
  logger->setLevel(level);
}

#endif /* ENABLE_GR_LOG */