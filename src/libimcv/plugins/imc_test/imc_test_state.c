/*
 * Copyright (C) 2011 Andreas Steffen, HSR Hochschule fuer Technik Rapperswil
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

#include "imc_test_state.h"

#include <debug.h>

typedef struct private_imc_test_state_t private_imc_test_state_t;

/**
 * Private data of an imc_test_state_t object.
 */
struct private_imc_test_state_t {

	/**
	 * Public members of imc_test_state_t
	 */
	imc_test_state_t public;

	/**
	 * TNCCS connection ID
	 */
	TNC_ConnectionID connection_id;

	/**
	 * TNCCS connection state
	 */
	TNC_ConnectionState state;

	/**
	 * Command to transmit to IMV
	 */
	char *command;

	/**
	 * Do a handshake retry
	 */
	bool handshake_retry;
};

METHOD(imc_state_t, get_connection_id, TNC_ConnectionID,
	private_imc_test_state_t *this)
{
	return this->connection_id;
}

METHOD(imc_state_t, change_state, void,
	private_imc_test_state_t *this, TNC_ConnectionState new_state)
{
	this->state = new_state;
}

METHOD(imc_state_t, destroy, void,
	private_imc_test_state_t *this)
{
	free(this->command);
	free(this);
}

METHOD(imc_test_state_t, get_command, char*,
	private_imc_test_state_t *this)
{
	return this->command;
}

METHOD(imc_test_state_t, set_command, void,
	private_imc_test_state_t *this, char* command)
{
	char *old_command;

	old_command = this->command;
	this->command = strdup(command);
	free(old_command);
}

METHOD(imc_test_state_t, do_handshake_retry, bool,
	private_imc_test_state_t *this)
{
	bool retry;

	/* test and reset handshake_retry flag */
	retry = this->handshake_retry;
	this->handshake_retry = FALSE;
	return retry;
}


/**
 * Described in header.
 */
imc_state_t *imc_test_state_create(TNC_ConnectionID connection_id,
								   char *command, bool retry)
{
	private_imc_test_state_t *this;

	INIT(this,
		.public = {
			.interface = {
				.get_connection_id = _get_connection_id,
				.change_state = _change_state,
				.destroy = _destroy,
			},
			.get_command = _get_command,
			.set_command = _set_command,
			.do_handshake_retry = _do_handshake_retry,
		},
		.state = TNC_CONNECTION_STATE_CREATE,
		.connection_id = connection_id,
		.command = strdup(command),
		.handshake_retry = retry,
	);
	
	return &this->public.interface;
}


