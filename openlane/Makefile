OPENLANE_ROOT ?= $(HOME)/OpenLane
OPENLANE_IMAGE ?= ghcr.io/the-openroad-project/openlane:latest
PROJECT_ROOT := $(abspath ..)
DESIGNS_DIR := $(PROJECT_ROOT)/openlane/designs

PDK_ROOT ?= $(HOME)/.ciel
PDK ?= sky130A
STD_CELL_LIBRARY ?= sky130_fd_sc_hd

DESIGN ?= soc_core_prod
DESIGN_PATH := /project/openlane/designs/$(DESIGN)

DOCKER_RUN = docker run --rm -it \
	-v $(OPENLANE_ROOT):/openlane \
	-v $(PROJECT_ROOT):/project \
	-v $(PDK_ROOT):$(PDK_ROOT) \
	-w /project/openlane \
	-e PWD=/project/openlane \
	-e PDK_ROOT=$(PDK_ROOT) \
	-e PDK=$(PDK) \
	-e STD_CELL_LIBRARY=$(STD_CELL_LIBRARY)

.PHONY: mount
mount:
	$(DOCKER_RUN) $(OPENLANE_IMAGE) /bin/bash

.PHONY: run
run:
	$(DOCKER_RUN) $(OPENLANE_IMAGE) /openlane/flow.tcl -design $(DESIGN_PATH)

.PHONY: clean
clean:
	rm -rf $(DESIGNS_DIR)/*/runs

# --- GDS Visualization ---
# Usage: make view-klayout [RUN=RUN_NAME]
# Usage: make view-magic [RUN=RUN_NAME]

# Find latest run if RUN is not specified
RUN ?= $(shell ls -dt $(DESIGNS_DIR)/$(DESIGN)/runs/* 2>/dev/null | head -n 1 | xargs basename)
RUN_PATH_INT := /project/openlane/designs/$(DESIGN)/runs/$(RUN)

# GDS path inside the container
GDS_FILE_INT := $(RUN_PATH_INT)/results/final/gds/soc_core.gds

DOCKER_GUI_RUN = docker run --rm -it \
	-v $(OPENLANE_ROOT):/openlane \
	-v $(PROJECT_ROOT):/project \
	-v $(PDK_ROOT):$(PDK_ROOT) \
	-v /tmp/.X11-unix:/tmp/.X11-unix \
	-e DISPLAY=$(DISPLAY) \
	-w /project/openlane \
	-e PWD=/project/openlane \
	-e PDK_ROOT=$(PDK_ROOT) \
	-e PDK=$(PDK) \
	-e STD_CELL_LIBRARY=$(STD_CELL_LIBRARY)

.PHONY: view-klayout
view-klayout:
	@echo "Opening KLayout for run: $(RUN)"
	$(DOCKER_GUI_RUN) $(OPENLANE_IMAGE) klayout \
		-rd design_name=$(DESIGN) \
		-rd in_gds=$(GDS_FILE_INT) \
		-rd tech_file=$(PDK_ROOT)/$(PDK)/libs.tech/klayout/tech/$(PDK).lyt

.PHONY: view-magic
view-magic:
	@echo "Opening Magic for run: $(RUN)"
	$(DOCKER_GUI_RUN) $(OPENLANE_IMAGE) magic \
		-rcfile $(PDK_ROOT)/$(PDK)/libs.tech/magic/$(PDK).magicrc \
		$(GDS_FILE_INT)
