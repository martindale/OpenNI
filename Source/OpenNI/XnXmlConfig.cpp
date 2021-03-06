/*****************************************************************************
*                                                                            *
*  OpenNI 1.0 Alpha                                                          *
*  Copyright (C) 2010 PrimeSense Ltd.                                        *
*                                                                            *
*  This file is part of OpenNI.                                              *
*                                                                            *
*  OpenNI is free software: you can redistribute it and/or modify            *
*  it under the terms of the GNU Lesser General Public License as published  *
*  by the Free Software Foundation, either version 3 of the License, or      *
*  (at your option) any later version.                                       *
*                                                                            *
*  OpenNI is distributed in the hope that it will be useful,                 *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the              *
*  GNU Lesser General Public License for more details.                       *
*                                                                            *
*  You should have received a copy of the GNU Lesser General Public License  *
*  along with OpenNI. If not, see <http://www.gnu.org/licenses/>.            *
*                                                                            *
*****************************************************************************/




//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include <XnOpenNI.h>
#include "XnXml.h"
#include <XnLog.h>
#include <XnStringsHash.h>
#include "XnLicensingInternal.h"

//---------------------------------------------------------------------------
// Code
//---------------------------------------------------------------------------
XnStatus xnXmlReadMapOutputMode(const TiXmlElement* pOpcode, XnMapOutputMode* pMapOutputMode)
{
	XnStatus nRetVal = XN_STATUS_OK;
	
	XnInt nValue;
	nRetVal = xnXmlReadIntAttribute(pOpcode, "xRes", &nValue);
	XN_IS_STATUS_OK(nRetVal);
	pMapOutputMode->nXRes = nValue;

	nRetVal = xnXmlReadIntAttribute(pOpcode, "yRes", &nValue);
	XN_IS_STATUS_OK(nRetVal);
	pMapOutputMode->nYRes = nValue;

	nRetVal = xnXmlReadIntAttribute(pOpcode, "FPS", &nValue);
	XN_IS_STATUS_OK(nRetVal);
	pMapOutputMode->nFPS = nValue;
	
	return (XN_STATUS_OK);
}

XnStatus xnXmlReadWaveOutputMode(const TiXmlElement* pOpcode, XnWaveOutputMode* pWaveOutputMode)
{
	XnStatus nRetVal = XN_STATUS_OK;

	XnInt nValue;
	nRetVal = xnXmlReadIntAttribute(pOpcode, "sampleRate", &nValue);
	XN_IS_STATUS_OK(nRetVal);
	pWaveOutputMode->nSampleRate = nValue;

	nRetVal = xnXmlReadIntAttribute(pOpcode, "bitsPerSample", &nValue);
	XN_IS_STATUS_OK(nRetVal);
	pWaveOutputMode->nBitsPerSample = nValue;

	nRetVal = xnXmlReadIntAttribute(pOpcode, "channels", &nValue);
	XN_IS_STATUS_OK(nRetVal);
	pWaveOutputMode->nChannels = nValue;

	return (XN_STATUS_OK);
}

XnStatus xnXmlReadCropping(const TiXmlElement* pOpcode, XnCropping* pCropping)
{
	XnStatus nRetVal = XN_STATUS_OK;
	
	nRetVal = xnXmlReadBoolAttribute(pOpcode, "enabled", &pCropping->bEnabled);
	XN_IS_STATUS_OK(nRetVal);
	
	XnInt nValue;
	nRetVal = xnXmlReadIntAttribute(pOpcode, "xOffset", &nValue);
	XN_IS_STATUS_OK(nRetVal);
	pCropping->nXOffset = nValue;

	nRetVal = xnXmlReadIntAttribute(pOpcode, "yOffset", &nValue);
	XN_IS_STATUS_OK(nRetVal);
	pCropping->nYOffset = nValue;

	nRetVal = xnXmlReadIntAttribute(pOpcode, "xSize", &nValue);
	XN_IS_STATUS_OK(nRetVal);
	pCropping->nXSize = nValue;

	nRetVal = xnXmlReadIntAttribute(pOpcode, "ySize", &nValue);
	XN_IS_STATUS_OK(nRetVal);
	pCropping->nYSize = nValue;
	
	return (XN_STATUS_OK);
}

XnStatus xnXmlReadVecotr3D(const TiXmlElement* pOpcode, XnVector3D* pVector)
{
	XnStatus nRetVal = XN_STATUS_OK;
	
	XnDouble dValue;
	nRetVal = xnXmlReadRealAttribute(pOpcode, "x", &dValue);
	XN_IS_STATUS_OK(nRetVal);
	pVector->X = (XnFloat)dValue;

	nRetVal = xnXmlReadRealAttribute(pOpcode, "y", &dValue);
	XN_IS_STATUS_OK(nRetVal);
	pVector->Y = (XnFloat)dValue;

	nRetVal = xnXmlReadRealAttribute(pOpcode, "z", &dValue);
	XN_IS_STATUS_OK(nRetVal);
	pVector->Z = (XnFloat)dValue;

	return (XN_STATUS_OK);
}

XnStatus xnXmlReadBoundingBox3D(const TiXmlElement* pElem, XnBoundingBox3D* pBox)
{
	XnStatus nRetVal = XN_STATUS_OK;
	
	const TiXmlElement* pMin;
	nRetVal = xnXmlGetChildElement(pElem, "Min", &pMin);
	XN_IS_STATUS_OK(nRetVal);

	nRetVal = xnXmlReadVecotr3D(pMin, &pBox->LeftBottomNear);
	XN_IS_STATUS_OK(nRetVal);
	
	const TiXmlElement* pMax;
	nRetVal = xnXmlGetChildElement(pElem, "Max", &pMax);
	XN_IS_STATUS_OK(nRetVal);

	nRetVal = xnXmlReadVecotr3D(pMax, &pBox->RightTopFar);
	XN_IS_STATUS_OK(nRetVal);

	return (XN_STATUS_OK);
}

XnStatus xnXmlReadUserPosition(const TiXmlElement* pOpcode, XnInt* pnIndex, XnBoundingBox3D* pUserPosition)
{
	XnStatus nRetVal = XN_STATUS_OK;
	
	nRetVal = xnXmlReadIntAttribute(pOpcode, "index", pnIndex);
	XN_IS_STATUS_OK(nRetVal);

	nRetVal = xnXmlReadBoundingBox3D(pOpcode, pUserPosition);
	XN_IS_STATUS_OK(nRetVal);

	return (XN_STATUS_OK);
}

XnStatus xnConfigureMirror(XnNodeHandle hNode, const TiXmlElement* pOpcode)
{
	XnStatus nRetVal = XN_STATUS_OK;
	
	XnBool bOn;
	nRetVal = xnXmlReadBoolAttribute(pOpcode, "on", &bOn);
	XN_IS_STATUS_OK(nRetVal);

	nRetVal = xnSetMirror(hNode, bOn);
	XN_IS_STATUS_OK(nRetVal);
	
	return (XN_STATUS_OK);
}

XnStatus xnConfigureMapOutputMode(XnNodeHandle hNode, const TiXmlElement* pOpcode)
{
	XnStatus nRetVal = XN_STATUS_OK;
	
	XnMapOutputMode Mode;
	nRetVal = xnXmlReadMapOutputMode(pOpcode, &Mode);
	XN_IS_STATUS_OK(nRetVal);

	nRetVal = xnSetMapOutputMode(hNode, &Mode);
	XN_IS_STATUS_OK(nRetVal);
	
	return (XN_STATUS_OK);
}

XnStatus xnConfigureWaveOutputMode(XnNodeHandle hNode, const TiXmlElement* pOpcode)
{
	XnStatus nRetVal = XN_STATUS_OK;

	XnWaveOutputMode Mode;
	nRetVal = xnXmlReadWaveOutputMode(pOpcode, &Mode);
	XN_IS_STATUS_OK(nRetVal);

	nRetVal = xnSetWaveOutputMode(hNode, &Mode);
	XN_IS_STATUS_OK(nRetVal);

	return (XN_STATUS_OK);
}

XnStatus xnConfigureCropping(XnNodeHandle hNode, const TiXmlElement* pOpcode)
{
	XnStatus nRetVal = XN_STATUS_OK;
	
	XnCropping Cropping;
	nRetVal = xnXmlReadCropping(pOpcode, &Cropping);
	XN_IS_STATUS_OK(nRetVal);

	nRetVal = xnSetCropping(hNode, &Cropping);
	XN_IS_STATUS_OK(nRetVal);
	
	return (XN_STATUS_OK);
}

XnStatus xnConfigurePixelFormat(XnNodeHandle hNode, const TiXmlElement* pOpcode)
{
	XnStatus nRetVal = XN_STATUS_OK;

	XnPixelFormat format;
	nRetVal = xnPixelFormatFromString(pOpcode->GetText(), &format);
	XN_IS_STATUS_OK(nRetVal);

	nRetVal = xnSetPixelFormat(hNode, format);
	XN_IS_STATUS_OK(nRetVal);

	return (XN_STATUS_OK);
}

XnStatus xnConfigureUserPosition(XnNodeHandle hNode, const TiXmlElement* pOpcode)
{
	XnStatus nRetVal = XN_STATUS_OK;
	
	XnInt nIndex;
	XnBoundingBox3D UserPosition;
	nRetVal = xnXmlReadUserPosition(pOpcode, &nIndex, &UserPosition);
	XN_IS_STATUS_OK(nRetVal);

	nRetVal = xnSetUserPosition(hNode, nIndex, &UserPosition);
	XN_IS_STATUS_OK(nRetVal);
	
	return (XN_STATUS_OK);
}

XnStatus xnConfigureProperty(XnNodeHandle hNode, const TiXmlElement* pOpcode)
{
	XnStatus nRetVal = XN_STATUS_OK;

	const XnChar* strName;
	nRetVal = xnXmlReadStringAttribute(pOpcode, "name", &strName);
	XN_IS_STATUS_OK(nRetVal);

	const XnChar* strType;
	nRetVal = xnXmlReadStringAttribute(pOpcode, "type", &strType);
	XN_IS_STATUS_OK(nRetVal);

	if (strcmp(strType, "int") == 0)
	{
		XnInt nValue;
		nRetVal = xnXmlReadIntAttribute(pOpcode, "value", &nValue);
		XN_IS_STATUS_OK(nRetVal);

		nRetVal = xnSetIntProperty(hNode, strName, nValue);
		XN_IS_STATUS_OK(nRetVal);
	}
	else if (strcmp(strType, "real") == 0)
	{
		XnDouble dValue;
		nRetVal = xnXmlReadRealAttribute(pOpcode, "value", &dValue);
		XN_IS_STATUS_OK(nRetVal);

		nRetVal = xnSetRealProperty(hNode, strName, dValue);
		XN_IS_STATUS_OK(nRetVal);
	}
	else if (strcmp(strType, "string") == 0)
	{
		const XnChar* strValue;
		nRetVal = xnXmlReadStringAttribute(pOpcode, "value", &strValue);
		XN_IS_STATUS_OK(nRetVal);

		nRetVal = xnSetStringProperty(hNode, strName, strValue);
		XN_IS_STATUS_OK(nRetVal);
	}
	else
	{
		XN_LOG_ERROR_RETURN(XN_STATUS_CORRUPT_FILE, XN_MASK_OPEN_NI, "Invalid property type: %s", strType);
	}

	return (XN_STATUS_OK);
}

XnStatus xnConfigureFrameSync(XnNodeHandle hNode, const TiXmlElement* pOpcode)
{
	XnStatus nRetVal = XN_STATUS_OK;
	
	XnContext* pContext = xnGetContextFromNodeHandle(hNode);
	XnNodeHandle hOther = NULL;

	nRetVal = xnGetNodeHandleByName(pContext, pOpcode->GetText(), &hOther);
	XN_IS_STATUS_OK(nRetVal);

	nRetVal = xnFrameSyncWith(hNode, hOther);
	XN_IS_STATUS_OK(nRetVal);
	
	return (XN_STATUS_OK);
}

XnStatus xnConfigureAlternativeViewPoint(XnNodeHandle hNode, const TiXmlElement* pOpcode)
{
	XnStatus nRetVal = XN_STATUS_OK;

	if (!xnIsCapabilitySupported(hNode, XN_CAPABILITY_ALTERNATIVE_VIEW_POINT))
	{
		return XN_STATUS_INVALID_OPERATION;
	}

	XnContext* pContext = xnGetContextFromNodeHandle(hNode);
	XnNodeHandle hOther = NULL;

	nRetVal = xnGetNodeHandleByName(pContext, pOpcode->GetText(), &hOther);
	XN_IS_STATUS_OK(nRetVal);

	nRetVal = xnSetViewPoint(hNode, hOther);
	XN_IS_STATUS_OK(nRetVal);

	return (XN_STATUS_OK);
}

XnStatus xnConfigureRecorderDestination(XnNodeHandle hNode, const TiXmlElement* pOpcode)
{
	XnStatus nRetVal = XN_STATUS_OK;

	XnRecordMedium medium = XN_RECORD_MEDIUM_FILE; // default

	if (pOpcode->Attribute("medium") != NULL)
	{
		const XnChar* strMedium;
		nRetVal = xnXmlReadStringAttribute(pOpcode, "medium", &strMedium);
		XN_IS_STATUS_OK(nRetVal);

		if (strcmp(strMedium, "File") == 0)
		{
			medium = XN_RECORD_MEDIUM_FILE;
		}
		else
		{
			XN_LOG_ERROR_RETURN(XN_STATUS_CORRUPT_FILE, XN_MASK_OPEN_NI, "Unknown recording medium: '%s'", strMedium);
		}
	}

	const XnChar* strName;
	nRetVal = xnXmlReadStringAttribute(pOpcode, "name", &strName);
	XN_IS_STATUS_OK(nRetVal);

	nRetVal = xnSetRecorderDestination(hNode, XN_RECORD_MEDIUM_FILE, strName);
	XN_IS_STATUS_OK(nRetVal);
	
	return (XN_STATUS_OK);
}

XnStatus xnConfigureAddNodeToRecording(XnNodeHandle hNode, const TiXmlElement* pOpcode)
{
	XnStatus nRetVal = XN_STATUS_OK;
	
	const XnChar* strName;
	nRetVal = xnXmlReadStringAttribute(pOpcode, "name", &strName);
	XN_IS_STATUS_OK(nRetVal);

	const XnChar* strCodec;
	nRetVal = xnXmlReadStringAttribute(pOpcode, "codec", &strCodec);
	XN_IS_STATUS_OK(nRetVal);

	// find node
	XnContext* pContext = xnGetContextFromNodeHandle(hNode);
	XnNodeHandle hOther = NULL;
	nRetVal = xnGetNodeHandleByName(pContext, strName, &hOther);
	XN_IS_STATUS_OK(nRetVal);

	// find codec
	if (strlen(strCodec) != sizeof(XnCodecID))
	{
		XN_LOG_ERROR_RETURN(XN_STATUS_CORRUPT_FILE, XN_MASK_OPEN_NI, "'%s' is not a valid codec ID!", strCodec);
	}

	XnCodecID codecID;
	xnOSMemCopy(&codecID, strCodec, sizeof(codecID));

	nRetVal = xnAddNodeToRecording(hNode, hOther, codecID);
	XN_IS_STATUS_OK(nRetVal);
	
	return (XN_STATUS_OK);
}

XnStatus xnConfigureSetOpcode(XnNodeHandle hNode, const TiXmlElement* pOpcode)
{
	XnStatus nRetVal = XN_STATUS_OK;

	const XnChar* strOpcode = pOpcode->Value();

	if (strcmp(strOpcode, "Mirror") == 0)
	{
		return xnConfigureMirror(hNode, pOpcode);
	}
	else if (strcmp(strOpcode, "MapOutputMode") == 0)
	{
		return xnConfigureMapOutputMode(hNode, pOpcode);
	}
	else if (strcmp(strOpcode, "WaveOutputMode") == 0)
	{
		return xnConfigureWaveOutputMode(hNode, pOpcode);
	}
	else if (strcmp(strOpcode, "Cropping") == 0)
	{
		return xnConfigureCropping(hNode, pOpcode);
	}
	else if (strcmp(strOpcode, "PixelFormat") == 0)
	{
		return xnConfigurePixelFormat(hNode, pOpcode);
	}
	else if (strcmp(strOpcode, "UserPosition") == 0)
	{
		return xnConfigureUserPosition(hNode, pOpcode);
	}
	else if (strcmp(strOpcode, "Property") == 0)
	{
		return xnConfigureProperty(hNode, pOpcode);
	}
	else if (strcmp(strOpcode, "FrameSync") == 0)
	{
		return xnConfigureFrameSync(hNode, pOpcode);
	}
	else if (strcmp(strOpcode, "AlternativeViewPoint") == 0)
	{
		return xnConfigureAlternativeViewPoint(hNode, pOpcode);
	}
	else if (strcmp(strOpcode, "RecorderDestination") == 0)
	{
		return xnConfigureRecorderDestination(hNode, pOpcode);
	}
	else if (strcmp(strOpcode, "AddNodeToRecording") == 0)
	{
		return xnConfigureAddNodeToRecording(hNode, pOpcode);
	}
	else
	{
		XN_LOG_WARNING_RETURN(XN_STATUS_CORRUPT_FILE, XN_MASK_OPEN_NI, "Invalid configuration option: %s", strOpcode);
	}
	
	return (XN_STATUS_OK);
}

XnStatus xnConfigureNodeFromXml(XnNodeHandle hNode, const TiXmlElement* pNode)
{
	XnStatus nRetVal = XN_STATUS_OK;
	
	const TiXmlElement* pConfig = pNode->FirstChildElement("Configuration");
	if (pConfig == NULL)
	{
		return (XN_STATUS_OK);
	}

	XnBool bLock = FALSE;
	const XnChar* strLock = pConfig->Attribute("lock");
	if (strLock != NULL)
	{
		xnXmlReadBoolAttribute(pConfig, "lock", &bLock);
	}

	XnLockHandle hLock;

	if (bLock)
	{
		nRetVal = xnLockNodeForChanges(hNode, &hLock);
		XN_IS_STATUS_OK(nRetVal);

		nRetVal = xnLockedNodeStartChanges(hNode, hLock);
		XN_IS_STATUS_OK(nRetVal);
	}

	const TiXmlElement* pOpcode = pConfig->FirstChildElement();
	while (pOpcode != NULL)
	{
		nRetVal = xnConfigureSetOpcode(hNode, pOpcode);
		XN_IS_STATUS_OK(nRetVal);

		pOpcode = pOpcode->NextSiblingElement();
	}

	if (bLock)
	{
		nRetVal = xnLockedNodeEndChanges(hNode, hLock);
	}

	return (XN_STATUS_OK);
}

static XnBool xnVersionGetNext(XnChar* strCurrent, XnChar** pstrNext)
{
	XnChar* strPoint = strchr(strCurrent, '.');
	if (strPoint == NULL)
	{
		return FALSE;
	}

	*strPoint = '\0';
	*pstrNext = strPoint + 1;

	return TRUE;
}

XnBool xnReadVersionFromString(const XnChar* strVersion, XnVersion* pVersion)
{
	XnChar csVersion[XN_MAX_NAME_LENGTH];
	strcpy(csVersion, strVersion);

	XnChar* strMajor = csVersion;
	XnChar* strMinor;
	XnChar* strMaintenance;
	XnChar* strBuild;

	if (xnVersionGetNext(strMajor, &strMinor) &&
		xnVersionGetNext(strMinor, &strMaintenance) &&
		xnVersionGetNext(strMaintenance, &strBuild))
	{
		if (0 == sscanf(strMajor, "%hhu", &pVersion->nMajor) ||
			0 == sscanf(strMinor, "%hhu", &pVersion->nMinor) ||
			0 == sscanf(strMaintenance, "%hu", &pVersion->nMaintenance) ||
			0 == sscanf(strBuild, "%u", &pVersion->nBuild))
		{
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}

XnStatus xnReadVersionFromXml(const TiXmlElement* pElem, XnVersion* pVersion)
{
	if (!xnReadVersionFromString(pElem->GetText(), pVersion))
	{
		XN_LOG_ERROR_RETURN(XN_STATUS_CORRUPT_FILE, XN_MASK_OPEN_NI,
			"Invalid '%s' xml entry - version string is not legal (line %u, col %u)!",
			pElem->Value(), pElem->Row(), pElem->Column());
	}

	return (XN_STATUS_OK);
}

XnStatus xnXmlReadQuery(const TiXmlElement* pQueryElem, XnNodeQuery* pQuery)
{
	XnStatus nRetVal = XN_STATUS_OK;
	
	// vendor
	const TiXmlElement* pVendor = pQueryElem->FirstChildElement("Vendor");
	if (pVendor != NULL)
	{
		xnNodeQuerySetVendor(pQuery, pVendor->GetText());
	}

	// name
	const TiXmlElement* pName = pQueryElem->FirstChildElement("Name");
	if (pName != NULL)
	{
		xnNodeQuerySetName(pQuery, pName->GetText());
	}

	// Min version
	const TiXmlElement* pMinVersion = pQueryElem->FirstChildElement("MinVersion");
	if (pMinVersion != NULL)
	{
		XnVersion minVersion;
		nRetVal = xnReadVersionFromXml(pMinVersion, &minVersion);
		XN_IS_STATUS_OK(nRetVal);

		xnNodeQuerySetMinVersion(pQuery, &minVersion);
	}

	// Max version
	const TiXmlElement* pMaxVersion = pQueryElem->FirstChildElement("MaxVersion");
	if (pMaxVersion != NULL)
	{
		XnVersion maxVersion;
		nRetVal = xnReadVersionFromXml(pMaxVersion, &maxVersion);
		XN_IS_STATUS_OK(nRetVal);

		xnNodeQuerySetMinVersion(pQuery, &maxVersion);
	}

	// Capabilities
	const TiXmlElement* pCapabilities = pQueryElem->FirstChildElement("Capabilities");
	if (pCapabilities != NULL)
	{
		const TiXmlElement* pCap = pCapabilities->FirstChildElement("Capability");
		while (pCap != NULL)
		{
			xnNodeQueryAddSupportedCapability(pQuery, pCap->GetText());
			pCap = pCap->NextSiblingElement("Capability");
		}
	}

	// Map Output Modes
	const TiXmlElement* pOutputModes = pQueryElem->FirstChildElement("MapOutputModes");
	if (pOutputModes != NULL)
	{
		const TiXmlElement* pMode = pOutputModes->FirstChildElement("MapOutputMode");
		while (pMode != NULL)
		{
			XnMapOutputMode Mode;
			nRetVal = xnXmlReadMapOutputMode(pMode, &Mode);
			XN_IS_STATUS_OK(nRetVal);

			xnNodeQueryAddSupportedMapOutputMode(pQuery, &Mode);

			pMode = pMode->NextSiblingElement("MapOutputMode");
		}
	}

	// Min User Position
	const TiXmlElement* pMinUserPositions = pQueryElem->FirstChildElement("MinUserPositions");
	if (pMinUserPositions != NULL)
	{
		XnInt nMinUserPositions;
		nRetVal = xnXmlReadTextAsInt(pMinUserPositions, &nMinUserPositions);
		XN_IS_STATUS_OK(nRetVal);

		xnNodeQuerySetSupportedMinUserPositions(pQuery, nMinUserPositions);
	}

	// Needed Nodes
	const TiXmlElement* pNeededNodes = pQueryElem->FirstChildElement("NeededNodes");
	if (pNeededNodes != NULL)
	{
		const TiXmlElement* pNode = pNeededNodes->FirstChildElement("Node");
		while (pNode != NULL)
		{
			xnNodeQueryAddNeededNode(pQuery, pNode->GetText());

			pNode = pNode->NextSiblingElement("Node");
		}
	}

	// Creation info
	const TiXmlElement* pCreationInfo = pQueryElem->FirstChildElement("CreationInfo");
	if (pCreationInfo != NULL)
	{
		xnNodeQuerySetCreationInfo(pQuery, pCreationInfo->GetText());
	}

	return (XN_STATUS_OK);
}

XnStatus xnConfigureCreateNodes(XnContext* pContext, const TiXmlElement* pRootElem, XnEnumerationErrors* pErrors)
{
	XnStatus nRetVal = XN_STATUS_OK;

	const TiXmlElement* pProudctionNodes = pRootElem->FirstChildElement("ProductionNodes");
	if (pProudctionNodes == NULL)
	{
		return (XN_STATUS_OK);
	}

	// global mirror
	const TiXmlElement* pGlobalMirror = pProudctionNodes->FirstChildElement("GlobalMirror");
	if (pGlobalMirror != NULL)
	{
		XnBool bOn;
		nRetVal = xnXmlReadBoolAttribute(pGlobalMirror, "on", &bOn);
		XN_IS_STATUS_OK(nRetVal);

		nRetVal = xnSetGlobalMirror(pContext, bOn);
		XN_IS_STATUS_OK(nRetVal);
	}

	// file recordings
	const TiXmlElement* pRecording = pProudctionNodes->FirstChildElement("Recording");
	if (pRecording != NULL)
	{
		const XnChar* strFileName;
		nRetVal = xnXmlReadStringAttribute(pRecording, "file", &strFileName);
		XN_IS_STATUS_OK(nRetVal);

		xnLogVerbose(XN_MASK_OPEN_NI, "Opening file recording '%s'...", strFileName);

		nRetVal = xnContextOpenFileRecording(pContext, strFileName);
		XN_IS_STATUS_OK(nRetVal);
	}

	const XnChar* strNodeTagName = "Node";
	const XnChar* strStartGeneratingAttr = "startGenerating";

	XnBool bStartGeneratingAll = TRUE;
	if (NULL != pProudctionNodes->Attribute(strStartGeneratingAttr))
	{
		nRetVal = xnXmlReadBoolAttribute(pProudctionNodes, strStartGeneratingAttr, &bStartGeneratingAll);
		XN_IS_STATUS_OK(nRetVal);
	}

	// new nodes
	const TiXmlElement* pNode = pProudctionNodes->FirstChildElement(strNodeTagName);
	while (pNode != NULL)
	{
		// get type
		const XnChar* strType;
		nRetVal = xnXmlReadStringAttribute(pNode, "type", &strType);
		XN_IS_STATUS_OK(nRetVal);

		xnLogVerbose(XN_MASK_OPEN_NI, "Requested to create a node of type %s...", strType);

		XnProductionNodeType Type;
		nRetVal = xnProductionNodeTypeFromString(strType, &Type);
		XN_IS_STATUS_OK(nRetVal);

		// check if there is a query
		XnNodeQuery* pQuery = NULL;
		const TiXmlElement* pQueryElem = pNode->FirstChildElement("Query");
		if (pQueryElem != NULL)
		{
			nRetVal = xnNodeQueryAllocate(&pQuery);
			XN_IS_STATUS_OK(nRetVal);

			nRetVal = xnXmlReadQuery(pQueryElem, pQuery);
			XN_IS_STATUS_OK(nRetVal);
		}

		// enumerate
		XnNodeInfoList* pTrees;
		nRetVal = xnEnumerateProductionTrees(pContext, Type, pQuery, &pTrees, pErrors);
		XN_IS_STATUS_OK(nRetVal);

		if (pQuery != NULL)
		{
			xnNodeQueryFree(pQuery);
			pQuery = NULL;
		}

		// choose first one
		XnNodeInfoListIterator itChosen = xnNodeInfoListGetFirst(pTrees);
		XnNodeInfo* pChosenInfo = xnNodeInfoListGetCurrent(itChosen);

		// check if a name was requested
		if (NULL != pNode->Attribute("name"))
		{
			const XnChar* strName = NULL;
			nRetVal = xnXmlReadStringAttribute(pNode, "name", &strName);
			if (nRetVal != XN_STATUS_OK)
			{
				xnNodeInfoListFree(pTrees);
				return (nRetVal);
			}

			nRetVal = xnNodeInfoSetInstanceName(pChosenInfo, strName);
			if (nRetVal != XN_STATUS_OK)
			{
				xnNodeInfoListFree(pTrees);
				return (nRetVal);
			}
		}

		// create it
		XnNodeHandle hNode;
		nRetVal = xnCreateProductionTree(pContext, pChosenInfo, &hNode);
		if (nRetVal != XN_STATUS_OK)
		{
			xnNodeInfoListFree(pTrees);
			return (nRetVal);
		}

		// free the list
		xnNodeInfoListFree(pTrees);

		// config it
		nRetVal = xnConfigureNodeFromXml(hNode, pNode);
		XN_IS_STATUS_OK(nRetVal);

		// check if we need to start it (if start generating all is on, it will be started at the end)
		XnBool bStart = FALSE;
		if (!bStartGeneratingAll)
		{
			if (NULL != pNode->Attribute(strStartGeneratingAttr))
			{
				nRetVal = xnXmlReadBoolAttribute(pNode, strStartGeneratingAttr, &bStart);
				XN_IS_STATUS_OK(nRetVal);
			}

			if (bStart)
			{
				nRetVal = xnStartGenerating(hNode);
				XN_IS_STATUS_OK(nRetVal);
			}
		}

		pNode = pNode->NextSiblingElement(strNodeTagName);
	}

	// start generating all
	if (bStartGeneratingAll)
	{
		nRetVal = xnStartGeneratingAll(pContext);
		XN_IS_STATUS_OK(nRetVal);
	}

	return (XN_STATUS_OK);
}

XN_C_API XnStatus xnContextRunXmlScriptFromFile(XnContext* pContext, const XnChar* strFileName, XnEnumerationErrors* pErrors)
{
	XnStatus nRetVal = XN_STATUS_OK;

	TiXmlDocument doc;
	nRetVal = xnXmlLoadDocument(doc, strFileName);
	XN_IS_STATUS_OK(nRetVal);

	TiXmlElement* pRootElem = doc.RootElement();
	if (pRootElem != NULL)
	{
		nRetVal = xnLoadLicensesFromXml(pContext, pRootElem);
		XN_IS_STATUS_OK(nRetVal);

		nRetVal = xnConfigureCreateNodes(pContext, pRootElem, pErrors);
		XN_IS_STATUS_OK(nRetVal);
	}

	return (XN_STATUS_OK);
}

