/* SPDX-License-Identifier: GPL-2.0 */
/* Copyright (C) 2018-2019, Intel Corporation. */

#ifndef _ICE_LIB_H_
#define _ICE_LIB_H_

#include "ice.h"

const char *ice_vsi_type_str(enum ice_vsi_type vsi_type);

bool ice_pf_state_is_nominal(struct ice_pf *pf);

void ice_update_eth_stats(struct ice_vsi *vsi);

int ice_vsi_cfg_single_rxq(struct ice_vsi *vsi, u16 q_idx);

int ice_vsi_cfg_single_txq(struct ice_vsi *vsi, struct ice_ring **tx_rings, u16 q_idx);

int ice_vsi_cfg_rxqs(struct ice_vsi *vsi);

int ice_vsi_cfg_lan_txqs(struct ice_vsi *vsi);

void ice_vsi_cfg_msix(struct ice_vsi *vsi);

int ice_vsi_manage_vlan_insertion(struct ice_vsi *vsi);

int ice_vsi_manage_vlan_stripping(struct ice_vsi *vsi, bool ena);

int ice_vsi_start_all_rx_rings(struct ice_vsi *vsi);

int ice_vsi_stop_all_rx_rings(struct ice_vsi *vsi);

int
ice_vsi_stop_lan_tx_rings(struct ice_vsi *vsi, enum ice_disq_rst_src rst_src,
			  u16 rel_vmvf_num);
#ifdef HAVE_XDP_SUPPORT

int ice_vsi_cfg_xdp_txqs(struct ice_vsi *vsi);

int ice_vsi_stop_xdp_tx_rings(struct ice_vsi *vsi);

#endif /* HAVE_XDP_SUPPORT */

bool ice_vsi_is_vlan_pruning_ena(struct ice_vsi *vsi);

int ice_cfg_vlan_pruning(struct ice_vsi *vsi, bool ena, bool vlan_promisc);

void ice_cfg_sw_lldp(struct ice_vsi *vsi, bool tx, bool create);

int ice_set_link(struct ice_vsi *vsi, bool ena);

void ice_vsi_delete(struct ice_vsi *vsi);
int ice_vsi_clear(struct ice_vsi *vsi);
void ice_vsi_put_qs(struct ice_vsi *vsi);

void ice_vsi_cfg_netdev_tc(struct ice_vsi *vsi, u8 ena_tc);

int ice_vsi_cfg_tc(struct ice_vsi *vsi, u8 ena_tc);

int ice_vsi_cfg_rss_lut_key(struct ice_vsi *vsi);

struct ice_vsi *
ice_vsi_setup(struct ice_pf *pf, struct ice_port_info *pi,
	      enum ice_vsi_type vsi_type, u16 vf_id, struct ice_channel *ch,
	      u8 tc);

void ice_napi_del(struct ice_vsi *vsi);

int ice_vsi_release(struct ice_vsi *vsi);

void ice_vsi_close(struct ice_vsi *vsi);

int ice_ena_vsi(struct ice_vsi *vsi, bool locked);

void ice_dis_vsi(struct ice_vsi *vsi, bool locked);

int ice_free_res(struct ice_res_tracker *res, u16 index, u16 id);

u16 ice_get_valid_res_count(struct ice_res_tracker *res);

int
ice_get_res(struct ice_pf *pf, struct ice_res_tracker *res, u16 needed, u16 id);

int ice_vsi_rebuild(struct ice_vsi *vsi, bool init_vsi);

bool ice_is_reset_in_progress(unsigned long *state);

void ice_vsi_dis_irq(struct ice_vsi *vsi);

void ice_vsi_free_irq(struct ice_vsi *vsi);

void ice_vsi_free_rx_rings(struct ice_vsi *vsi);

void ice_vsi_free_tx_rings(struct ice_vsi *vsi);

int ice_vsi_manage_rss_lut(struct ice_vsi *vsi, bool ena);

void ice_update_tx_ring_stats(struct ice_ring *ring, u64 pkts, u64 bytes);

void ice_update_rx_ring_stats(struct ice_ring *ring, u64 pkts, u64 bytes);

void ice_vsi_cfg_frame_size(struct ice_vsi *vsi);

int ice_status_to_errno(enum ice_status err);

void
ice_write_qrxflxp_cntxt(struct ice_hw *hw, u16 pf_q, u32 rxdid, u32 prio,
			bool __maybe_unused ena_ts);

#ifdef HAVE_NETPOLL_CONTROLLER
irqreturn_t ice_msix_clean_rings(int __always_unused irq, void *data);
#endif /* HAVE_NETPOLL_CONTROLLER */

u32 ice_intrl_usec_to_reg(u8 intrl, u8 gran);

enum ice_status
ice_vsi_cfg_mac_fltr(struct ice_vsi *vsi, const u8 *macaddr, bool set);
#ifdef FWLOG_SUPPORT
void ice_setup_fw_log(struct ice_pf *pf, u8 level, u32 events);
#endif /* FWLOG_SUPPORT */
bool ice_is_safe_mode(struct ice_pf *pf);
bool ice_is_peer_ena(struct ice_pf *pf);
bool ice_is_dflt_vsi_in_use(struct ice_sw *sw);
bool ice_is_vsi_dflt_vsi(struct ice_sw *sw, struct ice_vsi *vsi);
int ice_set_dflt_vsi(struct ice_sw *sw, struct ice_vsi *vsi);
int ice_clear_dflt_vsi(struct ice_sw *sw);
int ice_set_min_bw_limit(struct ice_vsi *vsi, u64 min_tx_rate);
int ice_set_max_bw_limit(struct ice_vsi *vsi, u64 max_tx_rate);
int ice_get_link_speed_kbps(struct ice_vsi *vsi);
int ice_get_link_speed_mbps(struct ice_vsi *vsi);
#endif /* !_ICE_LIB_H_ */
