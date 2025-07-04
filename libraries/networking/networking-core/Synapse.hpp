#pragma once


namespace Networking
{
	/**
	 *	Advanced connection handler with event system
	 *
	 * @tparam conn connection mode (TCP|UDP)
	 * @tparam mode synapse mode (CLIENT|SERVER)
	 */
	template <ConnectionMode conn, SynapseMode mode>
	class AXON_DECLSPEC Synapse : public BasicSynapse<conn, mode> {
	public:
#pragma region CONSTRUCTING
		/** Initializes Synapse in server mode */
		explicit Synapse(uint32_t port) : BasicSynapse<conn, mode>(port) {}
		/** Initialize Synapse in client mode */
		explicit Synapse(const ConnectionInfo &info) : BasicSynapse<conn, mode>(info) {}

		~Synapse() override = default;
#pragma endregion

#pragma region INTERFACE

		void update() override;
		void onMessageReceived(const AxonMessage&, SOCKADDR_IN_T*) override;

		EventSystem::AxonEventManager& getEventManager() { return events; }
        void sendTo(AxonMessage&, const SOCKADDR_IN_T*) override;
		void sendPooled(const AxonMessage&, const SOCKADDR_IN_T* = nullptr) const;
#pragma endregion
	protected:
		EventSystem::AxonEventManager events;

        std::vector<uint64_t> pendingValidation;
		std::unique_ptr<MessagePoolBase> pool = std::make_unique<MessagePoolBase>();
		std::unique_ptr<MessageMapBase> mmap = std::make_unique<MessageMapBase>();
	};

    /**
     *	Synapse with listen() function in separated thread.
     *
     * @tparam conn connection mode (TCP|UDP)
     * @tparam mode synapse mode (CLIENT|SERVER)
     */
	template <ConnectionMode conn, SynapseMode mode>
	class AXON_DECLSPEC AsyncSynapse final : public Synapse<conn, mode>
	{
	public:
		/** Initializes Synapse in server mode */
		explicit AsyncSynapse(uint32_t port) : Synapse<conn, mode>(port) {}

		/** Initialize Synapse in client mode */
		explicit AsyncSynapse(const ConnectionInfo& info) : Synapse<conn, mode>(info) {}

		~AsyncSynapse() override;

		void start() override;
		void kill() override;
	private:
		std::thread proc;
	};
}

#include "Synapse.ipp"

/* Synapse.hpp */
