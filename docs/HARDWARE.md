# Hardware Overview

The design combines an ESP32 Wi-Fi module, two relay channels, environmental-sensor connections, power regulation/protection, and external connectors.

## Files

- Original EasyEDA source: `Hardware/easyeda/source`
- EasyEDA previews: `Hardware/easyeda/previews`
- KiCad 10 project: `Hardware/kicad-10`
- Schematic PDF: `Hardware/kicad-10/exports/SmartFlowerPot_Schematic.pdf`
- Validation reports: `manufacturing/reports`

## Before manufacturing

1. Resolve all KiCad ERC and DRC errors.
2. Verify footprints, pin numbers, polarity, and manufacturer parts.
3. Confirm relay ratings, fuse, copper width, creepage, and clearance.
4. Generate fresh fabrication files only from the reviewed revision.
5. Test first with a current-limited low-voltage supply.

Do not use mains voltage on an exposed assembly. Use a suitable enclosure, strain relief, protective earth where required, over-current protection, and qualified review.
