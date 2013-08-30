/*
 * NetLink support
 *
 *    Francesco Salvestrini <f.salvestrini@nextworks.it>
 *    Leonardo Bergesio <leonardo.bergesio@i2cat.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef RINA_NETLINK_H
#define RINA_NETLINK_H

#include <linux/netlink.h>
#include <linux/genetlink.h>
#include <linux/skbuff.h>
#include <net/genetlink.h>
#include <net/netlink.h>
#include <net/sock.h>

#include "personality.h"

typedef enum {

	/* Unespecified operation */
	RINA_C_MIN = 0, 

	/* IPC Manager -> IPC Process */
	RINA_C_IPCM_ASSIGN_TO_DIF_REQUEST, 

	/* IPC Process -> IPC Manager */
	RINA_C_IPCM_ASSIGN_TO_DIF_RESPONSE, 

	/* IPC Manager -> IPC Process */
	RINA_C_IPCM_IPC_PROCESS_DIF_REGISTRATION_NOTIFICATION,

	/* IPC Manager -> IPC Process */
	RINA_C_IPCM_IPC_PROCESS_DIF_UNREGISTRATION_NOTIFICATION, 

	/* IPC Manager -> IPC Process */
	RINA_C_IPCM_ENROLL_TO_DIF_REQUEST, 

	/* IPC Process -> IPC Manager */
	RINA_C_IPCM_ENROLL_TO_DIF_RESPONSE, 

	/* IPC Manager -> IPC Process */
	RINA_C_IPCM_DISCONNECT_FROM_NEIGHBOR_REQUEST, 

	/* IPC Process -> IPC Manager */
	RINA_C_IPCM_DISCONNECT_FROM_NEIGHBOR_RESPONSE,

	/* IPC Manager -> IPC Process */
	RINA_C_IPCM_ALLOCATE_FLOW_REQUEST, 

	/* Allocate flow request from a remote application, 
	IPC Process -> IPC Manager */
	RINA_C_IPCM_ALLOCATE_FLOW_REQUEST_ARRIVED, 

	/* IPC Process -> IPC Manager */
	RINA_C_IPCM_ALLOCATE_FLOW_REQUEST_RESULT, 

	/* IPC Manager -> IPC Process */
	RINA_C_IPCM_ALLOCATE_FLOW_RESPONSE, 

	/* IPC Manager -> IPC Process */
	RINA_C_IPCM_DEALLOCATE_FLOW_REQUEST, 

	/* IPC Process -> IPC Manager*/
	RINA_C_IPCM_DEALLOCATE_FLOW_RESPONSE, 

	/*  IPC Process -> IPC Manager, flow deallocated without the */
	/*  application having requested it */
	RINA_C_IPCM_FLOW_DEALLOCATED_NOTIFICATION, 

	/*IPC Manager -> IPC Process */
	RINA_C_IPCM_REGISTER_APPLICATION_REQUEST, 

	/*IPC Process -> IPC Manager */
	RINA_C_IPCM_REGISTER_APPLICATION_RESPONSE, 

	/* IPC Manager -> IPC Process */
	RINA_C_IPCM_UNREGISTER_APPLICATION_REQUEST, 

	/* IPC Process -> IPC Manager */
	RINA_C_IPCM_UNREGISTER_APPLICATION_RESPONSE, 

	/* IPC Manager -> IPC Process */
	RINA_C_IPCM_QUERY_RIB_REQUEST, 

	/* IPC Process -> IPC Manager */
	RINA_C_IPCM_QUERY_RIB_RESPONSE, 

	/* IPC Process (user space) -> RMT (kernel) */
	RINA_C_RMT_ADD_FTE_REQUEST, 

	/* IPC Process (user space) -> RMT (kernel) */
	RINA_C_RMT_DELETE_FTE_REQUEST, 

	/* IPC Process (user space) -> RMT (kernel) */
	RINA_C_RMT_DUMP_FT_REQUEST, 

	/* RMT (kernel) -> IPC Process (user space) */
	RINA_C_RMT_DUMP_FT_REPLY,

	RINA_C_MAX,

} msg_id;

int  rina_netlink_init(void);
void rina_netlink_exit(void);

struct rina_nl_set;

struct genl_family  * get_nl_family(void);

struct rina_nl_set * rina_netlink_set_create(personality_id id);
int                  rina_netlink_set_destroy(struct rina_nl_set * set);

typedef int (* message_handler_cb)(void *             data,
                                   struct sk_buff *   buff,
                                   struct genl_info * info); 
int  rina_netlink_handler_register(struct rina_nl_set * set,
                                   msg_id               msg_type,
                                   void *               data,
                                   message_handler_cb   handler);
int  rina_netlink_handler_unregister(struct rina_nl_set * set,
                                     msg_id               msg_type);

int  rina_netlink_set_register(struct rina_nl_set * set);
int  rina_netlink_set_unregister(struct rina_nl_set * set);

#endif
