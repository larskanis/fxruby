<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version='1.0'
                xmlns="http://www.w3.org/TR/xhtml1/transitional"
                exclude-result-prefixes="#default">

<xsl:import href="/Users/lyle/docbook/docbook5-xsl-1.72.0/html/chunk.xsl"/>

<xsl:variable name="root.filename">book</xsl:variable>
<xsl:param name="html.stylesheet.type">text/css</xsl:param>
<xsl:param name="html.stylesheet">style.css</xsl:param>
<xsl:attribute-set name="shade.verbatim.style">
  <xsl:attribute name="width">100%</xsl:attribute>
</xsl:attribute-set>
<xsl:variable name="use.id.as.filename">1</xsl:variable>

</xsl:stylesheet>
