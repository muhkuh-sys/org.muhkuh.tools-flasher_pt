<?xml version="1.0" encoding="UTF-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="html" indent="no" omit-xml-declaration="yes" encoding="UTF-8"/>

<xsl:template match="/">
	<html>
		<xsl:comment>XSLT stylesheet used to transform this file:  spi_flash_types.xsl</xsl:comment>
		<xsl:apply-templates select="KnownSerialFlashes"/>

		<style type="text/css">
.result_ok {
        display: inline;
        width: 16px;
        height: 16px;
        background-image: url(data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAYAAAAf8/9hAAAABGdBTUEAAK/INwWK6QAAABl0RVh0U29mdHdhcmUAQWRvYmUgSW1hZ2VSZWFkeXHJZTwAAAGrSURBVDjLvZPZLkNhFIV75zjvYm7VGFNCqoZUJ+roKUUpjRuqp61Wq0NKDMelGGqOxBSUIBKXWtWGZxAvobr8lWjChRgSF//dv9be+9trCwAI/vIE/26gXmviW5bqnb8yUK028qZjPfoPWEj4Ku5HBspgAz941IXZeze8N1bottSo8BTZviVWrEh546EO03EXpuJOdG63otJbjBKHkEp/Ml6yNYYzpuezWL4s5VMtT8acCMQcb5XL3eJE8VgBlR7BeMGW9Z4yT9y1CeyucuhdTGDxfftaBO7G4L+zg91UocxVmCiy51NpiP3n2treUPujL8xhOjYOzZYsQWANyRYlU4Y9Br6oHd5bDh0bCpSOixJiWx71YY09J5pM/WEbzFcDmHvwwBu2wnikg+lEj4mwBe5bC5h1OUqcwpdC60dxegRmR06TyjCF9G9z+qM2uCJmuMJmaNZaUrCSIi6X+jJIBBYtW5Cge7cd7sgoHDfDaAvKQGAlRZYc6ltJlMxX03UzlaRlBdQrzSCwksLRbOpHUSb7pcsnxCCwngvM2Rm/ugUCi84fycr4l2t8Bb6iqTxSCgNIAAAAAElFTkSuQmCC);
        background-repeat: no-repeat;
        background-position: 0px - 16px;
        padding-left: 20px;
}

.result_failed {
        display: inline;
        width: 16px;
        height: 16px;
        background-image: url(data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAYAAAAf8/9hAAAAAXNSR0IArs4c6QAAAAZiS0dEAP8A/wD/oL2nkwAAAAlwSFlzAAALEwAACxMBAJqcGAAAAAd0SU1FB9sMAQwIIUTLrxoAAAKQSURBVDjLfZM9SJtRFIbf77Mx0RqCRqkGEbQWRSsBQTAKBZFCR+0kLSIOCg4dRFvoUBAUUTAiksWxVHAR4uAPOBTbQYtCJ6lY/ENbK2pTTUK+JPeeczoUf2pjH7jD4d73uXDOvRAR3LbOAgH5NT7eICL46fc//TkyYt08Y+Ia4YmJ+9drIYJo3X3c318iWrtZKYUbmDcCW2eBQO9FzUolWOv6ZDTab52ejlMikbXV1TV8u0DrcyEaAICQ33/OWttF65x0p/NZrs/nyGtpMVyFha/WW1tfXmQMEbkUhEZHG8D8XkTOzfR0l7O2FobNBn14iOOlJWRXVMBeXIwfs7NgIggRjNDY2DmYq7O7u7cB4HRoiGEYhsvngzo8BCcSgAiiOzuIh8NwFRdjY3Fxq25u7gEA3BGtM4R563R4+B1EnticTiOzshLJ/X2wZUFFIjBtNrgbG8GRCL4tLMBms61f9iCnpyedlfrESrVSMpmX6fUieXAAisWgwmEYpomMkhJYGxuACIQITrf78UZ7+4u/enDU1xd3uN12u8cDdXICFYnAMAzcLSuDtbcHiseRVV6O3WAQpLUIs0FEV1Ngpci022GkpUFHo4AIHIWFiO3sgOJxOAoKYO3tQSsFrVTuw8lJg5R6czVGkfGzzU2wZYGJkFFUhMTR0Z9wfj6Olpexv7ICUqrDOzUVAoDq6emBS4FncPA1E33cXViAs6oKkkxCiJDh8YAsC9FQ6OL2wFpzc2/KdwAAXzs7Pwjzo3teLwzTxPfVVcRjMUCkg4i2mSjIzC5mLq2fn9/+RwAAX9ra3mqlnpPWacIMIlquCQbrkYKUguusNTWtEFEtM5fWzc1t//czpaJmZsZHWism+pxq/zdPcqJhkKOO1AAAAABJRU5ErkJggg==);
        background-repeat: no-repeat;
        background-position: 0px - 16px;
        padding-left: 20px;
}

.result_error {
        display: inline;
        width: 16px;
        height: 16px;
        background-image: url(data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAYAAAAf8/9hAAAABGdBTUEAAK/INwWK6QAAABl0RVh0U29mdHdhcmUAQWRvYmUgSW1hZ2VSZWFkeXHJZTwAAAHdSURBVDjLpZNraxpBFIb3a0ggISmmNISWXmOboKihxpgUNGWNSpvaS6RpKL3Ry//Mh1wgf6PElaCyzq67O09nVjdVlJbSDy8Lw77PmfecMwZg/I/GDw3DCo8HCkZl/RlgGA0e3Yfv7+DbAfLrW+SXOvLTG+SHV/gPbuMZRnsyIDL/OASziMxkkKkUQTJJsLaGn8/iHz6nd+8mQv87Ahg2H9Th/BxZqxEkEgSrq/iVCvLsDK9awtvfxb2zjD2ARID+lVVlbabTgWYTv1rFL5fBUtHbbeTJCb3EQ3ovCnRC6xAgzJtOE+ztheYIEkqbFaS3vY2zuIj77AmtYYDusPy8/zuvunJkDKXM7tYWTiyGWFjAqeQnAD6+7ueNx/FLpRGAru7mcoj5ebqzszil7DggeF/DX1nBN82rzPqrzbRayIsLhJqMPT2N83Sdy2GApwFqRN7jFPL0tF+10cDd3MTZ2AjNUkGCoyO6y9cRxfQowFUbpufr1ct4ZoHg+Dg067zduTmEbq4yi/UkYidDe+kaTcP4ObJIajksPd/eyx3c+N2rvPbMDPbUFPZSLKzcGjKPrbJaDsu+dQO3msfZzeGY2TCvKGYQhdSYeeJjUt21dIcjXQ7U7Kv599f4j/oF55W4g/2e3b8AAAAASUVORK5CYII=);
        background-repeat: no-repeat;
        background-position: 0px - 16px;
        padding-left: 20px;
}


		</style>
	</html>
</xsl:template>

<xsl:template match="KnownSerialFlashes">
	<head>
		<title>SPI flash devices</title>
	</head>
	<body bgcolor="#ffffff" marginheight="2" marginwidth="2" topmargin="2" leftmargin="2">

	<table border="1">
		<xsl:for-each select="SerialFlash">
			<xsl:sort select="@name"/>
			<tr><td>
				<xsl:value-of select="@name"/>
			</td><td>
			<xsl:value-of select="Description"/><br/>
			<xsl:for-each select="Note">
				<xsl:value-of select="."/><br/>
			</xsl:for-each>
			Size: <xsl:value-of select="@size"/> bytes<br/>
			Clock: <xsl:value-of select="@clock"/> Hz<br/>
			Page size: <xsl:value-of select="Layout/@pageSize"/> bytes<br/>
			Sector size: <xsl:value-of select="Layout/@pageSize * Layout/@sectorPages"/> bytes<br/>
			
			</td><td>
			<div class="result_ok">
				Test1
			</div>
			</td><td>
			<div class="result_error">
				Test2
			</div>
			</td></tr>
		</xsl:for-each>
	</table>
	</body>
</xsl:template>

</xsl:stylesheet>
