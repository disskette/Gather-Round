#ifndef NETSUB_H
#define NETSUB_H

class Net_subscriber{
public:
    virtual void SendInfo() = 0;
    virtual ~Net_subscriber() = default;
};

#endif  // NETSUB_H