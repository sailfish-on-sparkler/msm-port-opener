#include <errno.h>
#include <string.h>
#include "qmi_dpm.h"

struct qmi_elem_info dpm_qmi_result_ei[] = {
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct dpm_qmi_result, result),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct dpm_qmi_result, error),
	},
	{}
};

struct qmi_elem_info dpm_hw_data_port_ei[] = {
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.offset = offsetof(struct dpm_hw_data_port, ep_type),
	},
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.offset = offsetof(struct dpm_hw_data_port, iface_id),
	},
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.offset = offsetof(struct dpm_hw_data_port, rx_ep),
	},
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.offset = offsetof(struct dpm_hw_data_port, tx_ep),
	},
	{}
};

struct qmi_elem_info dpm_open_port_req_ei[] = {
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 17,
		.offset = offsetof(struct dpm_open_port_req, hw_data_ports_valid),
	},
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 17,
		.offset = offsetof(struct dpm_open_port_req, hw_data_ports_len),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct dpm_hw_data_port),
		.array_type = VAR_LEN_ARRAY,
		.tlv_type = 17,
		.offset = offsetof(struct dpm_open_port_req, hw_data_ports),
		.ei_array = dpm_hw_data_port_ei,
	},
	{}
};

struct qmi_elem_info dpm_open_port_rsp_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct dpm_qmi_result),
		.tlv_type = 2,
		.offset = offsetof(struct dpm_open_port_rsp, result),
		.ei_array = dpm_qmi_result_ei,
	},
	{}
};

