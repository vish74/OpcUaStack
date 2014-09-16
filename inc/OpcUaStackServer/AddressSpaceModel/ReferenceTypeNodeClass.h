#ifndef __OpcUaStackServer_ReferenceTypeNodeClass_h__
#define __OpcUaStackServer_ReferenceTypeNodeClass_h__

#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackCore/Base/ObjectPool.h"
#include "OpcUaStackServer/AddressSpaceModel/BaseNodeClass.h"

namespace OpcUaStackServer
{

	class DLLEXPORT ReferenceTypeNodeClass : public BaseNodeClass, public ObjectPool<ReferenceTypeNodeClass>
	{
	  public:
		typedef boost::shared_ptr<ReferenceTypeNodeClass> SPtr;

		ReferenceTypeNodeClass(void);
		~ReferenceTypeNodeClass(void);

		IsAbstractAttribute& isAbstract(void);
		SymmetricAttribute& symmetric(void);
		InverseNameAttribute& inverseName(void);

	  private:
		// attributes mandatory
		IsAbstractAttribute isAbstract_;
		SymmetricAttribute symmetric_;
	
		// attributes optional
		InverseNameAttribute inverseName_;

		// references
		OpcUaNodeIdList hasProperty_;
		OpcUaNodeIdList hasSubtype_;

		// standard properties
		OpcUaString nodeVersion_;  // optional
	};

}

#endif