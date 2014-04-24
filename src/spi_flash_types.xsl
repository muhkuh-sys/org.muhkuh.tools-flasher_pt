<?xml version="1.0" encoding="UTF-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="html" indent="no" omit-xml-declaration="yes" encoding="UTF-8"/>

<xsl:template match="/">
	<html>
		<head>
			<title>SPI flash devices</title>
			<style type="text/css">
.result_true {
        display: inline;
        width: 16px;
        height: 16px;
        background-image: url(data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAYAAAAf8/9hAAAABGdBTUEAAK/INwWK6QAAABl0RVh0U29mdHdhcmUAQWRvYmUgSW1hZ2VSZWFkeXHJZTwAAAGrSURBVDjLvZPZLkNhFIV75zjvYm7VGFNCqoZUJ+roKUUpjRuqp61Wq0NKDMelGGqOxBSUIBKXWtWGZxAvobr8lWjChRgSF//dv9be+9trCwAI/vIE/26gXmviW5bqnb8yUK028qZjPfoPWEj4Ku5HBspgAz941IXZeze8N1bottSo8BTZviVWrEh546EO03EXpuJOdG63otJbjBKHkEp/Ml6yNYYzpuezWL4s5VMtT8acCMQcb5XL3eJE8VgBlR7BeMGW9Z4yT9y1CeyucuhdTGDxfftaBO7G4L+zg91UocxVmCiy51NpiP3n2treUPujL8xhOjYOzZYsQWANyRYlU4Y9Br6oHd5bDh0bCpSOixJiWx71YY09J5pM/WEbzFcDmHvwwBu2wnikg+lEj4mwBe5bC5h1OUqcwpdC60dxegRmR06TyjCF9G9z+qM2uCJmuMJmaNZaUrCSIi6X+jJIBBYtW5Cge7cd7sgoHDfDaAvKQGAlRZYc6ltJlMxX03UzlaRlBdQrzSCwksLRbOpHUSb7pcsnxCCwngvM2Rm/ugUCi84fycr4l2t8Bb6iqTxSCgNIAAAAAElFTkSuQmCC);
        background-repeat: no-repeat;
        background-position: 0px - 16px;
        padding-left: 20px;
}

.result_false {
        display: inline;
        width: 16px;
        height: 16px;
        background-image: url(data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAYAAAAf8/9hAAAABGdBTUEAAK/INwWK6QAAABl0RVh0U29mdHdhcmUAQWRvYmUgSW1hZ2VSZWFkeXHJZTwAAAHdSURBVDjLpZNraxpBFIb3a0ggISmmNISWXmOboKihxpgUNGWNSpvaS6RpKL3Ry//Mh1wgf6PElaCyzq67O09nVjdVlJbSDy8Lw77PmfecMwZg/I/GDw3DCo8HCkZl/RlgGA0e3Yfv7+DbAfLrW+SXOvLTG+SHV/gPbuMZRnsyIDL/OASziMxkkKkUQTJJsLaGn8/iHz6nd+8mQv87Ahg2H9Th/BxZqxEkEgSrq/iVCvLsDK9awtvfxb2zjD2ARID+lVVlbabTgWYTv1rFL5fBUtHbbeTJCb3EQ3ovCnRC6xAgzJtOE+ztheYIEkqbFaS3vY2zuIj77AmtYYDusPy8/zuvunJkDKXM7tYWTiyGWFjAqeQnAD6+7ueNx/FLpRGAru7mcoj5ebqzszil7DggeF/DX1nBN82rzPqrzbRayIsLhJqMPT2N83Sdy2GApwFqRN7jFPL0tF+10cDd3MTZ2AjNUkGCoyO6y9cRxfQowFUbpufr1ct4ZoHg+Dg067zduTmEbq4yi/UkYidDe+kaTcP4ObJIajksPd/eyx3c+N2rvPbMDPbUFPZSLKzcGjKPrbJaDsu+dQO3msfZzeGY2TCvKGYQhdSYeeJjUt21dIcjXQ7U7Kv599f4j/oF55W4g/2e3b8AAAAASUVORK5CYII=);
        background-repeat: no-repeat;
        background-position: 0px - 16px;
        padding-left: 20px;
}


			</style>
		</head>
		<body bgcolor="#ffffff" marginheight="2" marginwidth="2" topmargin="2" leftmargin="2">
			<h1>SPI flash devices</h1>
			<xsl:apply-templates select="KnownSerialFlashes"/>
		</body>
	</html>
</xsl:template>

<xsl:template match="KnownSerialFlashes">

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
				<xsl:variable name="isPageSizeOk" select="(Layout/@pageSize &gt;= 256) and (Layout/@pageSize &lt;= 4096)" />
				<xsl:variable name="isPageEraseOk" select="(Write/@eraseAndPageProgramCommand != '') or (Erase/@erasePageCommand != '')" />
				<xsl:variable name="isSectorSizeOk" select="(Layout/@pageSize*Layout/@sectorPages &gt;= 256) and (Layout/@pageSize*Layout/@sectorPages &lt;= 4096)" />
				<xsl:variable name="isSectorEraseOk" select="Erase/@eraseSectorCommand != ''" />
				<xsl:variable name="isRcxCompatible" select="($isPageSizeOk and $isPageEraseOk) or ($isSectorSizeOk and $isSectorEraseOk)" />
				<div class="{concat('result_', string($isRcxCompatible))}">
					rcX Compatibility:<br/>
					Page size: <xsl:value-of select="number($isRcxCompatible)" />
					<xsl:choose>
						<xsl:when test="$isPageSizeOk">
							OK
						</xsl:when>
						<xsl:otherwise>
							ERROR
						</xsl:otherwise>
					</xsl:choose>
					<br/>
					Page Erase:
					<xsl:choose>
						<xsl:when test="$isPageEraseOk">
							OK
						</xsl:when>
						<xsl:otherwise>
							ERROR
						</xsl:otherwise>
					</xsl:choose>
					<br/>
					<br/>
					Sector size:
					<xsl:choose>
						<xsl:when test="$isSectorSizeOk">
							OK
						</xsl:when>
						<xsl:otherwise>
							ERROR
						</xsl:otherwise>
					</xsl:choose>
					<br/>
					Sector Erase:
					<xsl:choose>
						<xsl:when test="$isSectorEraseOk">
							OK
						</xsl:when>
						<xsl:otherwise>
							ERROR
						</xsl:otherwise>
					</xsl:choose>
				</div>
			</td></tr>
		</xsl:for-each>
	</table>
</xsl:template>

</xsl:stylesheet>
