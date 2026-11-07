#include "QCA9377Controller.hpp"

OSDefineMetaClassAndStructors(QCA9377Controller, IOService);

bool QCA9377Controller::init(OSDictionary *dict) {
    return IOService::init(dict);
}

void QCA9377Controller::free(void) {
    IOService::free();
}

IOService* QCA9377Controller::probe(IOService *provider, SInt32 *score) {
    IOService *res = IOService::probe(provider, score);
    IOPCIDevice *device = OSDynamicCast(IOPCIDevice, provider);
    
    if (!device) return nullptr;

    UInt16 vendorID = device->configRead16(kIOPCIConfigVendorID);
    UInt16 deviceID = device->configRead16(kIOPCIConfigDeviceID);

    IOLog("QCA9377: Phat hien phan cung! Vendor ID: 0x%04X, Device ID: 0x%04X\n", vendorID, deviceID);

    if (vendorID == 0x168C && (deviceID == 0x0042 || deviceID == 0x003E)) {
        IOLog("QCA9377: Khop ma thiet bi mang Qualcomm Atheros hop le.\n");
        return res;
    }

    return nullptr;
}

bool QCA9377Controller::start(IOService *provider) {
    if (!IOService::start(provider)) return false;

    pciDevice = OSDynamicCast(IOPCIDevice, provider);
    if (!pciDevice) return false;

    pciDevice->open(this);
    pciDevice->setMemoryEnable(true);
    pciDevice->IOAccess(true);

    mmioMap = pciDevice->mapDeviceMemoryWithIndex(0);
    if (!mmioMap) {
        IOLog("QCA9377: Loi - Khong the anh xa vung nho MMIO (BAR0).\n");
        return false;
    }

    IOLog("QCA9377: Da anh xa thanh cong vung nho MMIO!\n");
    return true;
}

void QCA9377Controller::stop(IOService *provider) {
    if (mmioMap) {
        OSSafeReleaseNULL(mmioMap);
    }
    if (pciDevice) {
        pciDevice->close(this);
        pciDevice = nullptr;
    }
    IOService::stop(provider);
}
