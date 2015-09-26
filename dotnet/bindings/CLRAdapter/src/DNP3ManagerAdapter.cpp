
#include "DNP3ManagerAdapter.h"

#include "Conversions.h"
#include "LogAdapter.h"
#include "ChannelAdapter.h"

#include <asiodnp3/DNP3Manager.h>
#include <osslcrypto/CryptoProvider.h>

using namespace asiopal;

namespace Automatak
{
	namespace DNP3
	{
		namespace Adapter
		{

			IDNP3Manager^ DNP3ManagerFactory::CreateManager(System::Int32 concurrency)
			{
				return gcnew DNP3ManagerAdapter(concurrency);
			}

			IDNP3Manager^ DNP3ManagerFactory::CreateManager()
			{
				return gcnew DNP3ManagerAdapter(Environment::ProcessorCount);
			}


			DNP3ManagerAdapter::DNP3ManagerAdapter(System::Int32 concurrency) : 
				pCrypto(new osslcrypto::CryptoProvider()),
				pManager(new asiodnp3::DNP3Manager(concurrency, pCrypto))				
			{

			}

			DNP3ManagerAdapter::~DNP3ManagerAdapter()
			{
				delete pManager;
				delete pCrypto;
			}

			void DNP3ManagerAdapter::Shutdown()
			{
				pManager->Shutdown();
			}

			String^ DNP3ManagerAdapter::SSLVersion()
			{
				std::string version(pCrypto->Version());
				return Conversions::ConvertString(version);
			}

			IChannel^ DNP3ManagerAdapter::AddTCPClient(System::String^ id, System::UInt32 filters, ChannelRetry^ retry, System::String^ address, System::UInt16 port)
			{

				std::string stdName = Conversions::ConvertString(id);
				std::string stdAddress = Conversions::ConvertString(address);
				uint16_t stdPort = port;

				auto pChannel = pManager->AddTCPClient(stdName.c_str(), filters, Conversions::Convert(retry), stdAddress, "", stdPort);
				if (pChannel)
				{
					auto adapter = gcnew ChannelAdapter(pChannel, pCrypto);
					pChannel->DeleteOnDestruct(new gcroot<ChannelAdapter^>(adapter));
					return adapter;
				}
				else
				{
					return nullptr;
				}
			}

			IChannel^ DNP3ManagerAdapter::AddTCPServer(System::String^ id, System::UInt32 filters, ChannelRetry^ retry, System::String^ endpoint, System::UInt16 port)
			{
				std::string stdName = Conversions::ConvertString(id);
				std::string stdEndpoint = Conversions::ConvertString(endpoint);
				uint16_t stdPort = port;

				auto pChannel = pManager->AddTCPServer(stdName.c_str(), filters, Conversions::Convert(retry), stdEndpoint, stdPort);
				if (pChannel)
				{
					auto adapter = gcnew ChannelAdapter(pChannel, pCrypto);
					pChannel->DeleteOnDestruct(new gcroot<ChannelAdapter^>(adapter));
					return adapter;
				}
				else
				{
					return nullptr;
				}
			}

			IChannel^ DNP3ManagerAdapter::AddTLSClient(System::String^ id, System::UInt32 filters, ChannelRetry^ retry, System::String^ address, System::UInt16 port, Automatak::DNP3::Interface::TLSConfig^ config)
			{
				std::string stdName = Conversions::ConvertString(id);
				std::string stdAddress = Conversions::ConvertString(address);
				uint16_t stdPort = port;

				auto pChannel = pManager->AddTLSClient(stdName.c_str(), filters, Conversions::Convert(retry), stdAddress, "", stdPort, Conversions::Convert(config));
				if (pChannel)
				{
					auto adapter = gcnew ChannelAdapter(pChannel, pCrypto);
					pChannel->DeleteOnDestruct(new gcroot<ChannelAdapter^>(adapter));
					return adapter;
				}
				else
				{
					return nullptr;
				}
			}
			
			IChannel^ DNP3ManagerAdapter::AddTLSServer(System::String^ id, System::UInt32 filters, ChannelRetry^ retry, System::String^ endpoint, System::UInt16 port, Automatak::DNP3::Interface::TLSConfig^ config)
			{
				std::string stdName = Conversions::ConvertString(id);
				std::string stdEndpoint = Conversions::ConvertString(endpoint);
				uint16_t stdPort = port;

				auto pChannel = pManager->AddTLSServer(stdName.c_str(), filters, Conversions::Convert(retry), stdEndpoint, stdPort, Conversions::Convert(config));
				if (pChannel)
				{
					auto adapter = gcnew ChannelAdapter(pChannel, pCrypto);
					pChannel->DeleteOnDestruct(new gcroot<ChannelAdapter^>(adapter));
					return adapter;
				}
				else
				{
					return nullptr;
				}
			}

			IChannel^ DNP3ManagerAdapter::AddSerial(System::String^ id, System::UInt32 filters, ChannelRetry^ retry, Automatak::DNP3::Interface::SerialSettings^ settings)
			{
				std::string stdName = Conversions::ConvertString(id);
				auto s = Conversions::ConvertSerialSettings(settings);

				auto pChannel = pManager->AddSerial(stdName.c_str(), filters, Conversions::Convert(retry), s);
				if (pChannel)
				{
					auto adapter = gcnew ChannelAdapter(pChannel, pCrypto);
					pChannel->DeleteOnDestruct(new gcroot<ChannelAdapter^>(adapter));
					return adapter;
				}
				else
				{
					return nullptr;
				}
			}

			void DNP3ManagerAdapter::AddLogHandler(ILogHandler^ logHandler)
			{
				LogAdapterWrapper^ wrapper = gcnew LogAdapterWrapper(logHandler);
				pManager->AddLogSubscriber(wrapper->GetLogAdapter());
			}

		}
	}
}