#include "stdafx.h"
#include "ServiceLocator.h"

// Since it is static it need to be implemented
IAudioProvider* ServiceLocator::_audioProvider = NULL;
