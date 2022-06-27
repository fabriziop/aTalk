# .+ 
#
# .context    : aTalk, real time data communication
# .title      : root make file
# .kind       : make file
# .author     : Fabrizio Pollastri <mxgbot@gmail.com>
# .site       : Revello - Italy
# .creation   : 8-Dec-2019
# .copyright  : (c) 2019 Fabrizio Pollastri
# .license    : GNU Lesser General Public License version 3
# 
# .-

.PHONY: all all_doc all_src html clean

%.html: %.rst
	rst2html $< > $@

targets = README.html

all: $(targets) all_doc all_src

all_doc:
	$(MAKE) -C doc all

all_src:
	$(MAKE) -C src all

html: $(targets) html_doc

html_doc:
	$(MAKE) -C doc html

clean:
	rm -f *.html
	$(MAKE) -C doc clean
	$(MAKE) -C src clean
	$(MAKE) -C test clean

#### END ####
