########################################################################
#
# Generate the HTML documents from DocBook sources
#
########################################################################

SAXON = java -jar /Users/lyle/saxon-6.5.3/saxon.jar
HTML_STYLESHEET = custom-html.xsl
FO_STYLESHEET = custom-fo.xsl
FOP = /Users/lyle/fop-0.20.4/fop.sh

all: html

html:
	$(SAXON) book.xml $(HTML_STYLESHEET)

pdf:
	$(SAXON) book.xml $(FO_STYLESHEET) > book.fo
	$(FOP) book.fo book.pdf

clean:
	@rm -f *.html book.fo book.pdf
