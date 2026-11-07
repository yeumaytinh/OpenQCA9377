# OpenQCA9377

An experimental macOS Kernel Extension (kext) for Qualcomm Atheros QCA9377 Wi-Fi / Bluetooth PCIe adapters.

## 🚀 Status
- **Current State:** Early Development (PCI Matching & MMIO Mapping verified)
- **Target macOS:** macOS Ventura (13.x) & later
- **Vendor ID:** `0x168C`
- **Device IDs:** `0x0042`, `0x003E`

## 🛠 Features Implemented
- [x] PCI Matching & Initialization (`probe` / `start`)
- [x] MMIO BAR0 Memory Space Mapping
- [ ] Firmware loading (`firmware-5.bin`)
- [ ] `IO80211Controller` Integration (Wi-Fi Stack)

## 📌 Supported Hardware
- Qualcomm Atheros QCA9377 802.11ac Wireless Network Adapter

## ⚙️ Building
Requires Xcode 14+ or Command Line Tools on macOS:
```bash
clang++ -Xlinker -kext -nostdlib -lkmod -r -O2 QCA9377Controller.cpp -o QCA9377Driver
