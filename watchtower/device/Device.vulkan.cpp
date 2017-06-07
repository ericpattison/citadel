#include "Device.vulkan.h"

#include "../../keep/types.h"
#include "../../keep/constants.h"
#include "../../castle/game/Game.h"
#include <vulkan/vulkan.h>

#include <vector>
#include <assert.h>

class DeviceVulkan::Impl {
public:
	void Initialize() {
		CreateApplicationInfo();
		CreateInstanceInfo();
		CreateInstance();
		GetPhysicalDevices();
		CreateDevice();
	}

	void Shutdown() {
		DestroyInstance();
	}
private:
	VkApplicationInfo vkAppInfo;
	void CreateApplicationInfo() {
		vkAppInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		vkAppInfo.pNext = nullptr;
		vkAppInfo.pApplicationName = Game::Name().c_str();
		vkAppInfo.pEngineName = ENGINE_NAME;
		vkAppInfo.engineVersion = VK_MAKE_VERSION(ENGINE_VERSION_MAJOR, ENGINE_VERSION_MINOR, ENGINE_VERSION_PATCH);
		vkAppInfo.apiVersion = VK_MAKE_VERSION(1, 0, 3);
	}

	VkInstanceCreateInfo vkCreateInfo;
	std::vector<const char*> vkExtensions;
	void CreateInstanceInfo() {
		vkCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		vkCreateInfo.pNext = nullptr;
		vkCreateInfo.flags = 0;
		vkCreateInfo.pApplicationInfo = &vkAppInfo;

		vkExtensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);

		vkCreateInfo.enabledExtensionCount = vkExtensions.size();
		vkCreateInfo.ppEnabledExtensionNames = vkExtensions.data();
	}

	VkInstance vkInstance;
	void CreateInstance() {
		vkCreateInstance(&vkCreateInfo, nullptr, &vkInstance);
	}
	void DestroyInstance() {
		vkDestroyInstance(vkInstance, nullptr);
	}

	std::vector<VkPhysicalDevice> physicalDevices;
	void GetPhysicalDevices() {
		u32 count = 0;
		VkResult result = vkEnumeratePhysicalDevices(vkInstance, &count, nullptr);
		assert(result == VK_SUCCESS);
		assert(count >= 1);

		physicalDevices.resize(count);
		result = vkEnumeratePhysicalDevices(vkInstance, &count, physicalDevices.data());
		assert(result == VK_SUCCESS);
	}

	VkDevice device;
	void CreateDevice() {
		float priorities[] = { 1.0f };
		VkDeviceQueueCreateInfo queueInfo{};
		queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueInfo.pNext = nullptr;
		queueInfo.flags = 0;
		queueInfo.queueFamilyIndex = 0;
		queueInfo.queueCount = 1;
		queueInfo.pQueuePriorities = &priorities[0];

		std::vector<const char *> enabledExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
		VkDeviceCreateInfo deviceCreateInfo{};
		deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		deviceCreateInfo.pNext = nullptr;
		deviceCreateInfo.flags = 0;
		deviceCreateInfo.queueCreateInfoCount = 1;
		deviceCreateInfo.pQueueCreateInfos = &queueInfo;
		deviceCreateInfo.enabledExtensionCount = enabledExtensions.size();
		deviceCreateInfo.ppEnabledExtensionNames = enabledExtensions.data();
		deviceCreateInfo.pEnabledFeatures = nullptr;

		VkResult result = vkCreateDevice(physicalDevices[0], &deviceCreateInfo, nullptr, &device);
		assert(result == VK_SUCCESS);
	}
};

DeviceVulkan::DeviceVulkan() {
	Initialize();
}

DeviceVulkan::~DeviceVulkan() {
	Shutdown();
}

void DeviceVulkan::Initialize() {
	impl = std::make_shared<DeviceVulkan::Impl>();
	impl->Initialize();
}

void DeviceVulkan::Shutdown() {
	impl->Shutdown();
}
