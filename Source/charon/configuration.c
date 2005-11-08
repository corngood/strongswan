/**
 * @file configuration.c
 * 
 * @brief Class configuration_t. 
 * Object of this type represents a configuration for an IKE_SA
 * 
 */

/*
 * Copyright (C) 2005 Jan Hutter, Martin Willi
 * Hochschule fuer Technik Rapperswil
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.  See <http://www.fsf.org/copyleft/gpl.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */

#include <stdlib.h>
#include <freeswan.h>
#include <pluto/constants.h>
#include <pluto/defs.h>

#include "types.h"
#include "configuration.h"

/**
 * Private data of an configuration_t object
 */
typedef struct private_configuration_s private_configuration_t;
 
struct private_configuration_s { 	

	/**
	 * Public part of a configuration_t object
	 */
	configuration_t public;
	 
	 
	/* Private values */

};

/**
 * @brief implements function destroy of configuration_t
 */
static status_t destroy (private_configuration_t *this)
{
	if (this == NULL)
	{
		return FAILED;
	}
	pfree(this);
	return SUCCESS;
}

/*
 * Described in Header-File
 */
configuration_t * configuration_create()
{
	private_configuration_t *this = alloc_thing(private_configuration_t, "private_configuration_t");
	if (this == NULL)
	{
		return NULL;
	}
	
	/* Public functions */
	this->public.destroy = (status_t(*)(configuration_t*))destroy;

	
	return (&this->public);	
}
