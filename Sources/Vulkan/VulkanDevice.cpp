#include "Vulkan/VulkanDevice.hpp"

// ----- Accessible only inside the file ----- //

void createInstance(std::shared_ptr<Device> device);
void createSurface(std::shared_ptr<Device> device, GLFWwindow *window);
void pickPhysicalDevice(std::shared_ptr<Device> device);
void createLogicalDevice(std::shared_ptr<Device> device);
void createSwapChain(std::shared_ptr<Device> device);
void createImages(std::shared_ptr<Device> device);
void createCommandPool(std::shared_ptr<Device> device);
void createSemaphores(std::shared_ptr<Device> device, VkSemaphore &semaphore);
void fillPresentInfos(std::shared_ptr<Device> device);


bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR &surface);
bool checkDeviceExtensionSupport(VkPhysicalDevice device);
uint32_t evaluateDevice(VkPhysicalDevice device);
QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR &surface);











void createInstance(std::shared_ptr<Device> device) { 

    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Vulkan Tuto";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "Gulg Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0; //Min vulkan API required

    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;

    createInfo.enabledLayerCount = 0;

    checkVulkanError(vkCreateInstance(&createInfo, nullptr, &device->instance), "GulgEngine can't create VkInstance.");   
}

void createSurface(std::shared_ptr<Device> device, GLFWwindow *window) {

    checkVulkanError(glfwCreateWindowSurface(device->instance, window, nullptr, &device->surface), "GulgEngine can't create VkSurface.");
}

void pickPhysicalDevice(std::shared_ptr<Device> device) {
    
    uint32_t deviceCount{0};
    vkEnumeratePhysicalDevices(device->instance, &deviceCount, nullptr);
    if(deviceCount == 0) { throw std::runtime_error("Vulkan device initialization error: no physical device available."); }

    std::vector<VkPhysicalDevice> devices{deviceCount};
    vkEnumeratePhysicalDevices(device->instance, &deviceCount, devices.data());

    uint32_t bestScore{0}, currentScore{0};

    for(const VkPhysicalDevice &currentDevice: devices) {

        currentScore = evaluateDevice(currentDevice);

        if(isDeviceSuitable(currentDevice, device->surface) && currentScore > bestScore) {

            device->physicalDevice = currentDevice;
            bestScore = currentScore;
            break;
        }
    }


    if(bestScore == 0) { throw std::runtime_error("Vulkan device initialization error: no suitable device available."); }
}

void createLogicalDevice(std::shared_ptr<Device> device) {

    QueueFamilyIndices indices{findQueueFamilies(device->physicalDevice, device->surface)};
   
    float queuePriority{1.f};
    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = {indices.graphics.value(), indices.present.value()};

    for(uint32_t queueFamily: uniqueQueueFamilies) {

        VkDeviceQueueCreateInfo queueCreateInfo = {};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    VkPhysicalDeviceFeatures deviceFeatures = {};

    VkDeviceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    createInfo.pEnabledFeatures = &deviceFeatures;
    createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = deviceExtensions.data();
    createInfo.enabledLayerCount = 0;

    checkVulkanError(vkCreateDevice(device->physicalDevice, &createInfo, nullptr, &device->logicalDevice), "GulgEngine can't create logic device->");
    vkGetDeviceQueue(device->logicalDevice, indices.graphics.value(), 0, &device->graphicsQueue);
    vkGetDeviceQueue(device->logicalDevice, indices.present.value(), 0, &device->presentQueue);
}

void createSwapChain(std::shared_ptr<Device> device) {

	SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device->physicalDevice, device->surface);

	VkSurfaceFormatKHR swapFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
	VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
	VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities, device->width, device->height);

	uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
	if (swapChainSupport.capabilities.maxImageCount > 0 
	 && imageCount > swapChainSupport.capabilities.maxImageCount) {

	    imageCount = swapChainSupport.capabilities.maxImageCount;
	}

	VkSwapchainCreateInfoKHR createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.surface = device->surface;
	createInfo.minImageCount = imageCount;
	createInfo.imageFormat = swapFormat.format;
	createInfo.imageColorSpace = swapFormat.colorSpace;
	createInfo.imageExtent = extent;
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	QueueFamilyIndices indices = findQueueFamilies(device->physicalDevice, device->surface);
	uint32_t queueFamilyIndices[] = {indices.graphics.value(), indices.present.value()};

	if (indices.graphics != indices.present) {

	    createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
	    createInfo.queueFamilyIndexCount = 2;
	    createInfo.pQueueFamilyIndices = queueFamilyIndices;
	} 

	else {

	    createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	    createInfo.queueFamilyIndexCount = 0; // Optional
	    createInfo.pQueueFamilyIndices = nullptr; // Optional
	}

	createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	createInfo.presentMode = presentMode;
	createInfo.clipped = VK_TRUE;
	createInfo.oldSwapchain = VK_NULL_HANDLE;

	checkVulkanError(vkCreateSwapchainKHR(device->logicalDevice, &createInfo, nullptr, &device->swapChain), "GulgEngine can't create VkSwapchainKHR.");
}


void createImages(std::shared_ptr<Device> device) {

	uint32_t imageCount{0};
	vkGetSwapchainImagesKHR(device->logicalDevice, device->swapChain, &imageCount, nullptr);
    device->images.resize(imageCount);
    vkGetSwapchainImagesKHR(device->logicalDevice, device->swapChain, &imageCount, device->images.data());

    SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device->physicalDevice, device->surface);

	VkSurfaceFormatKHR swapFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);

    for(size_t i{0}; i < imageCount; i++) {

    	VkImageViewCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createInfo.image = device->images[i];
		createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		createInfo.format = swapFormat.format;
		createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		createInfo.subresourceRange.baseMipLevel = 0;
		createInfo.subresourceRange.levelCount = 1;
		createInfo.subresourceRange.baseArrayLayer = 0;
		createInfo.subresourceRange.layerCount = 1;

		VkImageView newView;

		checkVulkanError(vkCreateImageView(device->logicalDevice, &createInfo, nullptr, &newView), "GulgEngine can't create VkImageView.");

		device->imageViews.emplace_back(newView);
	}
}


void createCommandPool(std::shared_ptr<Device> device) {

	QueueFamilyIndices queueFamilyIndices = findQueueFamilies(device->physicalDevice, device->surface);

	VkCommandPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.queueFamilyIndex = queueFamilyIndices.graphics.value();

	checkVulkanError(vkCreateCommandPool(device->logicalDevice, &poolInfo, nullptr, &device->commandPool), "GulgEngine can't create VkCommandPool.");
}


void createSemaphores(std::shared_ptr<Device> device, VkSemaphore &semaphore) {

	VkSemaphoreCreateInfo semaphoreInfo = {};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    checkVulkanError(vkCreateSemaphore(device->logicalDevice, &semaphoreInfo, nullptr, &semaphore), "GulgEngine can't create VkSemaphore."); 
}




bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR &surface) {

    QueueFamilyIndices indices{findQueueFamilies(device, surface)};

    bool extensionsSupported{checkDeviceExtensionSupport(device)}, swapChainAdequate{false};
    if (extensionsSupported) {

        SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device, surface);
        swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
    }

    return indices.isComplete() && extensionsSupported && swapChainAdequate;
}

bool checkDeviceExtensionSupport(VkPhysicalDevice device) {

    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

    std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

    for (const VkExtensionProperties &extension : availableExtensions) { requiredExtensions.erase(extension.extensionName); }

    return requiredExtensions.empty();
}

uint32_t evaluateDevice(VkPhysicalDevice device) {

    VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceFeatures deviceFeatures;

    vkGetPhysicalDeviceProperties(device, &deviceProperties);
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
    uint32_t score{0};

    // Discrete GPUs have a significant performance advantage
    if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) { score += 1000; }

    // Maximum possible size of textures affects graphics quality
    score += deviceProperties.limits.maxImageDimension2D;

    // Application can't function without geometry shaders
    if(!deviceFeatures.geometryShader) { score = 0; }

    return score;
}

QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR &surface) {

    QueueFamilyIndices indices;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    uint32_t i = 0;

    for(const VkQueueFamilyProperties &queueFamily : queueFamilies) {

        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) { indices.graphics = i; }

        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

        if(presentSupport) { indices.present = i;  }
        if (indices.isComplete()) {  break; }
        i++;
    }

    return indices;
}




// ----- Accessible outside the file ----- //

std::shared_ptr<Device> createVulkanDevice(GLFWwindow *window, const uint32_t width, const uint32_t height) {

	std::shared_ptr<Device> workingDevice{std::make_shared<Device>()};
	workingDevice->width = width;
	workingDevice->height = height;

	try { createInstance(workingDevice); }
	catch(const std::exception &e) { throw e; }

	try { createSurface(workingDevice, window); }
	catch(const std::exception &e) { 

		vkDestroyInstance(workingDevice->instance, nullptr);
		throw e;
	}

	try { pickPhysicalDevice(workingDevice); }
	catch(const std::exception &e) { 

		vkDestroyInstance(workingDevice->instance, nullptr);
		throw e;
	}

    try { createLogicalDevice(workingDevice); }
	catch(const std::exception &e) { 

		vkDestroySurfaceKHR(workingDevice->instance, workingDevice->surface, nullptr);
		vkDestroyInstance(workingDevice->instance, nullptr);

		throw e;
	}

	try { createSwapChain(workingDevice); }
	catch(const std::exception &e) { 

		vkDestroyDevice(workingDevice->logicalDevice, nullptr);
		vkDestroySurfaceKHR(workingDevice->instance, workingDevice->surface, nullptr);
		vkDestroyInstance(workingDevice->instance, nullptr);

		throw e;
	}

	try { createImages(workingDevice); }
	catch(const std::exception &e) { 

		vkDestroySwapchainKHR(workingDevice->logicalDevice, workingDevice->swapChain, nullptr);
		vkDestroyDevice(workingDevice->logicalDevice, nullptr);
		vkDestroySurfaceKHR(workingDevice->instance, workingDevice->surface, nullptr);
		vkDestroyInstance(workingDevice->instance, nullptr);
		throw e;
	}

	try { createCommandPool(workingDevice); }
	catch(const std::exception &e) { 

		for(VkImageView current_view: workingDevice->imageViews) { vkDestroyImageView(workingDevice->logicalDevice, current_view, nullptr); }

		vkDestroySwapchainKHR(workingDevice->logicalDevice, workingDevice->swapChain, nullptr);
		vkDestroyDevice(workingDevice->logicalDevice, nullptr);
		vkDestroySurfaceKHR(workingDevice->instance, workingDevice->surface, nullptr);
		vkDestroyInstance(workingDevice->instance, nullptr);

		throw e;
	}

	try { createSemaphores(workingDevice, workingDevice->readyForGraphics); }
	catch(const std::exception &e) { 

		vkDestroyCommandPool(workingDevice->logicalDevice, workingDevice->commandPool, nullptr);

		for(VkImageView current_view: workingDevice->imageViews) { vkDestroyImageView(workingDevice->logicalDevice, current_view, nullptr); }

		vkDestroySwapchainKHR(workingDevice->logicalDevice, workingDevice->swapChain, nullptr);
		vkDestroyDevice(workingDevice->logicalDevice, nullptr);
		vkDestroySurfaceKHR(workingDevice->instance, workingDevice->surface, nullptr);
		vkDestroyInstance(workingDevice->instance, nullptr);

		throw e;
	}

	try { createSemaphores(workingDevice, workingDevice->readyForPresent); }
	catch(const std::exception &e) { 

		vkDestroySemaphore(workingDevice->logicalDevice, workingDevice->readyForGraphics, nullptr);
		vkDestroyCommandPool(workingDevice->logicalDevice, workingDevice->commandPool, nullptr);

		for(VkImageView current_view: workingDevice->imageViews) { vkDestroyImageView(workingDevice->logicalDevice, current_view, nullptr); }

		vkDestroySwapchainKHR(workingDevice->logicalDevice, workingDevice->swapChain, nullptr);
		vkDestroyDevice(workingDevice->logicalDevice, nullptr);
		vkDestroySurfaceKHR(workingDevice->instance, workingDevice->surface, nullptr);
		vkDestroyInstance(workingDevice->instance, nullptr);

		throw e;
	}

	fillPresentInfos(workingDevice);

    return workingDevice;
}


void fillPresentInfos(std::shared_ptr<Device> device) {

	device->presentInfo = {};
	device->presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

	device->presentInfo.pWaitSemaphores = &device->readyForPresent;
	device->presentInfo.waitSemaphoreCount = 1;
	
	device->presentInfo.pSwapchains = &device->swapChain;
	device->presentInfo.swapchainCount = 1;

	device->presentInfo.pImageIndices = &device->currentImageIndex;
}