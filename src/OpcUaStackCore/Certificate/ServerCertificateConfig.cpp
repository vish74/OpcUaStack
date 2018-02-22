/*
   Copyright 2018 Kai Huebl (kai@huebl-sgh.de)

   Lizenziert gemäß Apache Licence Version 2.0 (die „Lizenz“); Nutzung dieser
   Datei nur in Übereinstimmung mit der Lizenz erlaubt.
   Eine Kopie der Lizenz erhalten Sie auf http://www.apache.org/licenses/LICENSE-2.0.

   Sofern nicht gemäß geltendem Recht vorgeschrieben oder schriftlich vereinbart,
   erfolgt die Bereitstellung der im Rahmen der Lizenz verbreiteten Software OHNE
   GEWÄHR ODER VORBEHALTE – ganz gleich, ob ausdrücklich oder stillschweigend.

   ServerCertificateConfigrmationen über die jeweiligen Bedingungen für Genehmigungen und Einschränkungen
   im Rahmen der Lizenz finden Sie in der Lizenz.

   Autor: Kai Huebl (kai@huebl-sgh.de)
 */

#include "OpcUaStackCore/Base/Log.h"
#include "OpcUaStackCore/Certificate/ServerCertificateConfig.h"

namespace OpcUaStackCore
{

	ServerCertificateConfig::ServerCertificateConfig(void)
	{
	}

	ServerCertificateConfig::~ServerCertificateConfig(void)
	{
	}

	bool
	ServerCertificateConfig::parse(
		ServerCertificate::SPtr& serverCertificate,
		const std::string& configPrefix,
		Config* childConfig,
		const std::string& configurationFileName
	)
	{
		// checks if server certificate configuration exists
		boost::optional<Config> child = childConfig->getChild(configPrefix);
		if (!child) {
			Log(Info, "server certificate is disabled");
			return true;
		}

		// get certificate trust list location
		std::string certificateTrustListLocation;
		if (!child->getConfigParameter("CertificateTrustListLocation", certificateTrustListLocation) == true) {
			Log(Error, "mandatory parameter not found in configuration")
				.parameter("ConfigurationFileName", configurationFileName)
				.parameter("ParameterPath", configPrefix + std::string(".CertificateTrustListLocation"));
			return false;
		}
		serverCertificate->certificateTrustListLocation(certificateTrustListLocation);

		// get certificate revocation list location
		std::string certificateRevocationListLocation;
		if (!child->getConfigParameter("CertificateRevocationListLocation", certificateRevocationListLocation) == true) {
			Log(Error, "mandatory parameter not found in configuration")
				.parameter("ConfigurationFileName", configurationFileName)
				.parameter("ParameterPath", configPrefix + std::string(".CertificateRevocationListLocation"));
			return false;
		}
		serverCertificate->certificateRevocationListLocation(certificateRevocationListLocation);

		// get issuer certificates location
		std::string issuersCertificatesLocation;
		if (!child->getConfigParameter("IssuersCertificatesLocation", issuersCertificatesLocation) == true) {
			Log(Error, "mandatory parameter not found in configuration")
				.parameter("ConfigurationFileName", configurationFileName)
				.parameter("ParameterPath", configPrefix + std::string(".IssuersCertificatesLocation"));
			return false;
		}
		serverCertificate->issuersCertificatesLocation(issuersCertificatesLocation);

		// get issuer revocation list location
		std::string issuersRevocationListLocation;
		if (!child->getConfigParameter("IssuersRevocationListLocation", issuersRevocationListLocation) == true) {
			Log(Error, "mandatory parameter not found in configuration")
				.parameter("ConfigurationFileName", configurationFileName)
				.parameter("ParameterPath", configPrefix + std::string(".IssuersRevocationListLocation"));
			return false;
		}
		serverCertificate->issuersRevocationListLocation(issuersRevocationListLocation);

		// get reject list location
		std::string rejectListLocation;
		if (!child->getConfigParameter("RejectListLocation", rejectListLocation) == true) {
			Log(Error, "mandatory parameter not found in configuration")
				.parameter("ConfigurationFileName", configurationFileName)
				.parameter("ParameterPath", configPrefix + std::string(".RejectListLocation"));
			return false;
		}
		serverCertificate->rejectListLocation(rejectListLocation);

		// get private key location
		std::string privateKeyLocation;
		if (!child->getConfigParameter("PrivateKeyLocation", privateKeyLocation) == true) {
			Log(Error, "mandatory parameter not found in configuration")
				.parameter("ConfigurationFileName", configurationFileName)
				.parameter("ParameterPath", configPrefix + std::string(".PrivateKeyLocation"));
			return false;
		}
		serverCertificate->privateKeyLocation(privateKeyLocation);

		return true;
	}

}