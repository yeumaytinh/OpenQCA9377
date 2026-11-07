#ifndef _QCA9377_CONTROLLER_HPP_
#define _QCA9377_CONTROLLER_HPP_

#include <IOKit/IOService.h>
#include <IOKit/pci/IOPCIDevice.h>
#include <IOKit/IOLib.h>

class QCA9377Controller : public IOService {
    OSDeclareDefaultStructors(QCA9377Controller);

public:
    virtual bool init(OSDictionary *dictionary = nullptr) override;
    virtual void free(void) override;
    virtual IOService* probe(IOService *provider, SInt32 *score) override;
    virtual bool start(IOService *provider) override;
    virtual void stop(IOService *provider) override;

private:
    IOPCIDevice *pciDevice;
    IOMemoryMap *mmioMap;
};

#endif /* _QCA9377_CONTROLLER_HPP_ */
