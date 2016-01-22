/*
 * Copyright 2014-2016 Nippon Telegraph and Telephone Corporation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/*
 * Note: this file originally auto-generated by mib2c using
 *        : mib2c.scalar.conf 11805 2005-01-07 09:37:18Z dts12 $
 */

#include <stdint.h>
#include <stdbool.h>

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>

#include "dot1dBaseNumPorts.h"
#include "dataplane_interface.h"

/** Initializes the dot1dBaseNumPorts module */
void
init_dot1dBaseNumPorts(void) {
  static oid dot1dBaseNumPorts_oid[] = { 1,3,6,1,2,1,17,1,2 };

  DEBUGMSGTL(("dot1dBaseNumPorts", "Initializing\n"));

  netsnmp_register_scalar(
    netsnmp_create_handler_registration("dot1dBaseNumPorts",
                                        handle_dot1dBaseNumPorts,
                                        dot1dBaseNumPorts_oid, OID_LENGTH(dot1dBaseNumPorts_oid),
                                        HANDLER_CAN_RONLY
                                       ));
}

int
handle_dot1dBaseNumPorts(netsnmp_mib_handler *handler,
                         netsnmp_handler_registration *reginfo,
                         netsnmp_agent_request_info   *reqinfo,
                         netsnmp_request_info         *requests) {
  int32_t port_num;
  size_t num;
  (void) handler;
  (void) reginfo;

  switch (reqinfo->mode) {

    case MODE_GET:
      if (dataplane_bridge_count_port(&num) == LAGOPUS_RESULT_OK) {
        port_num = (int32_t) num;
        snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                 (u_char *) &port_num,
                                 sizeof(port_num));
        break;
      }
    default:
      /* we should never get here, so this is a really bad error */
      snmp_log(LOG_ERR, "unknown mode (%d) in handle_dot1dBaseNumPorts\n",
               reqinfo->mode );
      return SNMP_ERR_GENERR;
  }

  return SNMP_ERR_NOERROR;
}
