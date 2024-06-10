#include <errno.h>
#include <libqrtr.h>
#include <stdio.h>

#include "qmi_dpm.h"

int main(void)
{
	uint8_t data_buf[256];
	struct qrtr_ctrl_pkt ctrl_pkt;
	struct qrtr_packet qmi_pkt = { .data = data_buf };
	int ret;
	int fd = qrtr_open(0);
	uint32_t node, port;
	uint32_t dpm_node, dpm_port;
	struct dpm_open_port_req open_port_req = {
		.hw_data_ports_valid = true,
		.hw_data_ports_len = 1,
		.hw_data_ports = {
			{ .ep_type = 5, .iface_id = 1, .rx_ep = 1, .tx_ep = 1 },
		},
	};

	if (fd < 0) {
		perror("qrtr_open failed");
		return -1;
	}

	ret = qrtr_new_lookup(fd, QMI_SERVICE_DPM, 0, 0);
	if (ret < 0) {
		perror("qrtr_new_lookup for dpm service failed");
		return -1;
	}

	do {
		ret = qrtr_recvfrom(fd, &ctrl_pkt, sizeof(ctrl_pkt), &node, &port);
		if (ret < 0) {
			perror("qrtr_recv after lookup failed");
			return -1;
		}
		if (port != QRTR_PORT_CTRL) {
			fprintf(stderr, "ignoring non-control packet from (%u, %u)\n", node, port);
			continue;
		}
		if (ret != sizeof(ctrl_pkt)) {
			fprintf(stderr, "control packet has wrong size (%d)\n", ret);
			return -1;
		}
		fprintf(stderr, "qrtr control packet: %08x\n", ctrl_pkt.cmd);
	} while (ctrl_pkt.cmd != QRTR_TYPE_NEW_SERVER && ctrl_pkt.server.service != QMI_SERVICE_DPM);

	dpm_node = ctrl_pkt.server.node;
	dpm_port = ctrl_pkt.server.port;

	fprintf(stderr, "dpm is at (%u, %u)\n", dpm_node, dpm_port);

	qmi_pkt.data_len = sizeof(data_buf);
	if (qmi_encode_message(&qmi_pkt, QMI_REQUEST, DPM_OPEN_PORT, 1,
				&open_port_req, dpm_open_port_req_ei) < 0)
	{
		fprintf(stderr, "failed to encode dpm_open_port_req\n");
		return -1;
	}

	ret = qrtr_sendto(fd, dpm_node, dpm_port, qmi_pkt.data, qmi_pkt.data_len);
	if (ret < 0) {
		fprintf(stderr, "failed to send dpm_open_port_req\n");
		return -1;
	}

	do {
		ret = qrtr_recvfrom(fd, qmi_pkt.data, sizeof(data_buf), &node, &port);
		if (ret < 0) {
			perror("qrtr_recv for dpm_open_port_rsp failed");
			return -1;
		}
		if (node != dpm_node && port != dpm_port) {
			fprintf(stderr, "ignoring non-dpm packet from (%u, %u)\n", node, port);
			continue;
		}
	} while (0);

	fprintf(stderr, "got dpm response\n");

	return 0;
}
