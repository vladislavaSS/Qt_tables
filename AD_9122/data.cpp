#include "AD9122-widget.h"


QStringList itemNames = {
    "Comm", "Power Control", "Data Format", "Interrupt Enable", "Interrupt Enable",
    "Event Flag", "Clock Receiver Control", "PLL Control", "PLL Status",
    "Sync Control", "Sync Status", "Data Receiver Status", "DCI Delay", "FIFO Control",
    "FIFO Status", "Datapath Control", "HB1 Control", "HB2 Control", "HB3 Control",
    "Chip ID", "FTW LSB", "FTW", "FTW", "FTW MSB",
    "NCO Phase Offset LSB", "NCO Phase Offset MSB", "NCO FTW Update", "I Phase Adj LSB", "I Phase Adj MSB",
    "Q Phase Adj LSB", "Q Phase Adj MSB", "I DAC Offset LSB", "I DAC Offset MSB", "Q DAC Offset LSB", "Q DAC Offset MSB", "I DAC FS Adjust",
    "I DAC Control", "I Aux DAC Data", "I Aux DAC Control", "Q DAC FS Adjust", "Q DAC Control", "Q Aux DAC Data", "Q Aux DAC Control",
    "Die Temp Range Control", "Die Temp LSB", "Die Temp MSB", "SED Control",
    "Compare I0 LSBs", "Compare I0 MSBs", "Compare Q0 LSBs", "Compare Q0 MSBs",
    "Compare I1 LSBs", "Compare I1 MSBs", "Compare Q1 LSBs", "Compare Q1 MSBs",
    "SED I LSBs", "SED I MSBs", "SED Q LSBs", "SED Q MSBs",
    "Revision"
};

QStringList regNames = {
    "0x00", "0x01", "0x03", "0x04", "0x05",
    "0x06", "0x07", "0x08", "0x0A", "0x0C",
    "0x0D", "0x0E", "0x0F", "0x10", "0x11",
    "0x12", "0x13", "0x15", "0x16", "0x17",
    "0x18", "0x19", "0x1B", "0x1C", "0x1D",
    "0x1E", "0x1F", "0x30", "0x31", "0x32",
    "0x33", "0x34", "0x35", "0x36", "0x38",
    "0x39", "0x3A", "0x3B", "0x3C", "0x3D",
    "0x3E", "0x3F", "0x40", "0x41", "0x42",
    "0x43", "0x44", "0x45", "0x46", "0x47",
    "0x48", "0x49", "0x4A", "0x67", "0x68",
    "0x69", "0x6A", "0x6B", "0x6C", "0x6D",
    "0x6E", "0x6F", "0x70", "0x71", "0x72",
    "0x73", "0x7F"
};
