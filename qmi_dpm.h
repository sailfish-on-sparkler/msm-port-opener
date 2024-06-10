#ifndef __QMI_DPM_H__
#define __QMI_DPM_H__

#include <stdint.h>
#include <stdbool.h>

#include "libqrtr.h"

#define QMI_SERVICE_DPM 47
#define DPM_OPEN_PORT 32

struct dpm_qmi_result {
	uint16_t result;
	uint16_t error;
};

struct dpm_hw_data_port {
	uint32_t ep_type;
	uint32_t iface_id;
	uint32_t rx_ep;
	uint32_t tx_ep;
};

struct dpm_open_port_req {
	bool hw_data_ports_valid;
	uint32_t hw_data_ports_len;
	struct dpm_hw_data_port hw_data_ports[1];
};

struct dpm_open_port_rsp {
	struct dpm_qmi_result result;
};

extern struct qmi_elem_info dpm_open_port_req_ei[];
extern struct qmi_elem_info dpm_open_port_rsp_ei[];

#endif
