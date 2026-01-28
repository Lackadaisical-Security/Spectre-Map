# AI/ML Engine - Complete Integration Guide

## Overview

SpectreMap includes a complete AI/ML engine that integrates **TensorFlow 2.x C++ API** and **Brain.js** neural networks for real-time threat detection, behavioral analysis, anomaly detection, and attack path prediction.

## Architecture

The AI/ML system consists of three main components:

1. **TensorFlow Backend** (`tensorflow_backend.cpp`) - Production-grade deep learning
2. **Brain.js Backend** (`brainjs_backend.cpp`) - Lightweight neural networks via V8
3. **Extended Thinking Engine** (`extended_thinking.cpp`) - Multi-stage reasoning system

### Component Diagram

```
┌─────────────────────────────────────────────────┐
│           AIMLEngine (Unified API)              │
├─────────────────────────────────────────────────┤
│  • Hardware Detection & Selection               │
│  • Model Management & Caching                   │
│  • Inference Coordination                       │
└────────────┬─────────────────┬──────────────────┘
             │                 │
    ┌────────▼────────┐   ┌───▼──────────────┐
    │ TensorFlow      │   │ Brain.js         │
    │ Backend         │   │ Backend          │
    ├─────────────────┤   ├──────────────────┤
    │ • SavedModel    │   │ • V8 Engine      │
    │ • GPU Accel     │   │ • Feedforward NN │
    │ • Quantization  │   │ • LSTM/RNN       │
    └─────────────────┘   └──────────────────┘
```

## Build Configuration

### Build Options

```cmake
option(ENABLE_TENSORFLOW "Enable TensorFlow AI/ML" OFF)
option(ENABLE_BRAINJS "Enable Brain.js neural networks" OFF)
option(ENABLE_CUDA "Enable NVIDIA CUDA acceleration" OFF)
option(ENABLE_ROCM "Enable AMD ROCm acceleration" OFF)
option(ENABLE_METAL "Enable Apple Metal acceleration" OFF)
```

### Building Without Dependencies (Default)

The AI/ML engine is built by default in **stub mode** - it provides the complete API but logs warnings when TensorFlow or V8 are not available:

```bash
mkdir build && cd build
cmake ..
make spectremap_ai
```

### Building With TensorFlow Support

```bash
# Install TensorFlow C++ library
# Ubuntu/Debian:
sudo apt-get install libtensorflow-dev

# Or build from source:
# git clone https://github.com/tensorflow/tensorflow
# bazel build //tensorflow:libtensorflow.so

# Build SpectreMap with TensorFlow
cmake .. -DENABLE_TENSORFLOW=ON
make spectremap_ai
```

### Building With Brain.js Support

```bash
# Install V8 JavaScript engine
sudo apt-get install libv8-dev

# Build SpectreMap with Brain.js
cmake .. -DENABLE_BRAINJS=ON
make spectremap_ai
```

## Usage Examples

### 1. Hardware Detection

```cpp
#include "ai/ai_ml_engine.h"

using namespace SpectreMap;

AIMLEngine engine;

// Detect available hardware
auto hardware = engine.detectAvailableHardware();
for (const auto& hw : hardware) {
    LOG_INFO("Device: " + hw.device_name);
    LOG_INFO("Memory: " + std::to_string(hw.memory_mb) + " MB");
    LOG_INFO("FP16 Support: " + std::string(hw.supports_fp16 ? "Yes" : "No"));
}

// Get optimal hardware
auto optimal = engine.getOptimalHardware();
LOG_INFO("Selected: " + optimal.device_name);

// Manually set hardware
engine.setHardware(AIMLEngine::HardwareType::CUDA_GPU, 0);
```

### 2. TensorFlow Model Loading

```cpp
// Configure TensorFlow model
AIMLEngine::TFModelConfig config;
config.type = AIMLEngine::TFModelType::THREAT_CLASSIFIER;
config.model_path = "/path/to/model/threat_classifier";
config.input_shape = {1, 784};
config.output_shape = {1, 10};
config.use_quantization = true;  // Use INT8 quantization
config.use_mixed_precision = false;
config.batch_size = 32;
config.confidence_threshold = 0.7f;

// Load model
bool loaded = engine.loadTensorFlowModel("threat_classifier", config);
if (loaded) {
    LOG_INFO("Model loaded successfully");
}
```

### 3. TensorFlow Inference

```cpp
// Prepare input data
std::vector<float> network_features(784);
// ... populate features from network scan ...

// Run inference
auto result = engine.predictTensorFlow("threat_classifier", network_features);

LOG_INFO("Predicted class: " + result.label);
LOG_INFO("Confidence: " + std::to_string(result.confidence));
LOG_INFO("Inference time: " + std::to_string(result.inference_time_ms) + "ms");

// Access class probabilities
for (const auto& [class_name, probability] : result.class_probabilities) {
    LOG_INFO(class_name + ": " + std::to_string(probability));
}
```

### 4. Brain.js Neural Network

```cpp
// Create Brain.js network
AIMLEngine::BrainJSConfig config;
config.type = AIMLEngine::BrainJSModelType::LSTM;
config.input_size = 10;
config.hidden_layers = {20, 15};
config.output_size = 5;
config.activation = "sigmoid";
config.learning_rate = 0.3;
config.iterations = 1000;
config.error_threshold = 0.005;

bool created = engine.createBrainJSModel("pattern_recognizer", config);

// Train the network
std::vector<std::vector<float>> inputs = {
    {0.1, 0.2, 0.3, ...},
    {0.4, 0.5, 0.6, ...},
    // ... more training samples
};

std::vector<std::vector<float>> outputs = {
    {1, 0, 0, 0, 0},
    {0, 1, 0, 0, 0},
    // ... corresponding outputs
};

bool trained = engine.trainBrainJSModel("pattern_recognizer", inputs, outputs);

// Run prediction
std::vector<float> test_input = {0.5, 0.6, 0.7, ...};
auto result = engine.predictBrainJS("pattern_recognizer", test_input);
```

### 5. Extended Thinking - Threat Analysis

```cpp
#include "ai/extended_thinking.h"

using namespace SpectreMap;

ExtendedThinking thinking;

// Configure reasoning
thinking.setReasoningDepth(5);        // 5 stages of analysis
thinking.enableSelfCritique(true);     // Enable critique loops
thinking.setConfidenceThreshold(0.7f); // Minimum confidence
thinking.setReasoningMode(ExtendedThinking::ReasoningMode::ANALYTICAL);

// Analyze threat
std::map<std::string, float> threat_features;
threat_features["port_scan_detected"] = 0.9f;
threat_features["unusual_traffic_pattern"] = 0.7f;
threat_features["known_malicious_ip"] = 0.8f;

auto result = thinking.analyzeThreat(threat_features, "Network scan from 192.168.1.100");

// Access reasoning stages
for (const auto& stage : result.reasoning_stages) {
    LOG_INFO("Stage: " + stage.stage_name);
    LOG_INFO("Reasoning: " + stage.reasoning);
    LOG_INFO("Confidence: " + std::to_string(stage.confidence));
    
    for (const auto& point : stage.key_points) {
        LOG_INFO("  - " + point);
    }
}

LOG_INFO("Final Answer: " + result.final_answer);
LOG_INFO("Overall Confidence: " + std::to_string(result.overall_confidence));

// Alternative hypotheses
for (const auto& hypothesis : result.alternative_hypotheses) {
    LOG_INFO("Alternative: " + hypothesis);
}
```

### 6. Anomaly Detection

```cpp
// Detect anomalies in time-series data
std::vector<float> network_metrics = {
    100, 105, 98, 102, 99,  // Normal
    500, 520, 510,          // Anomaly!
    95, 100, 103            // Normal
};

auto anomaly_result = thinking.analyzeAnomaly(network_metrics, "Network bandwidth (Mbps)");

LOG_INFO("Analysis: " + anomaly_result.final_answer);

// Or use AI/ML engine's built-in anomaly detector
auto ml_result = engine.detectAnomaly(network_metrics);
if (ml_result.is_anomaly) {
    LOG_WARNING("Anomaly detected!");
    LOG_WARNING("Score: " + std::to_string(ml_result.anomaly_score));
    LOG_WARNING("Type: " + ml_result.anomaly_type);
}
```

### 7. Behavior Analysis

```cpp
// Analyze user/entity behavior
std::vector<std::map<std::string, std::string>> events;

events.push_back({
    {"time", "08:00"},
    {"action", "login"},
    {"ip", "192.168.1.50"}
});

events.push_back({
    {"time", "08:05"},
    {"action", "file_access"},
    {"file", "/etc/passwd"}
});

events.push_back({
    {"time", "08:10"},
    {"action", "ssh_connection"},
    {"target", "remote_server"}
});

auto behavior_analysis = thinking.analyzeBehavior(events, "admin_user");

LOG_INFO("Behavior Analysis: " + behavior_analysis.final_answer);
```

## Integration with SpectreMap Modules

### NetworkScanner Integration

```cpp
// In NetworkScanner::performScan()
auto threat_level = m_aiEngine->predictThreatLevel(scan_results);
if (threat_level > 0.8f) {
    LOG_WARNING("High threat detected: " + std::to_string(threat_level));
    notifySecurityTeam();
}
```

### ThreatMapper Integration

```cpp
// In ThreatMapper::analyzeEntity()
auto behavior_pattern = m_aiEngine->analyzeBehavior(entity_history);
auto attack_paths = m_aiEngine->predictAttackPaths(current_state);

for (const auto& path : attack_paths) {
    visualizeAttackPath(path);
}
```

## Performance Characteristics

### Stub Mode (No TensorFlow/V8)
- **Initialization**: < 1ms
- **Memory**: < 1MB
- **Inference**: Logs warning, returns dummy data
- **Use Case**: Development, CI/CD, systems without ML libraries

### TensorFlow Mode
- **Initialization**: 100-500ms (model loading)
- **Memory**: 100MB - 2GB (depending on model)
- **Inference (CPU)**: 10-100ms
- **Inference (GPU)**: 1-10ms
- **Throughput (GPU)**: 1000+ predictions/second

### Brain.js Mode
- **Initialization**: 10-50ms
- **Memory**: 1-10MB
- **Inference**: 1-5ms
- **Training**: Seconds to minutes
- **Use Case**: Lightweight patterns, edge devices

## Model Directory Structure

```
models/
├── tensorflow/
│   ├── threat_classifier/
│   │   ├── saved_model.pb
│   │   └── variables/
│   ├── anomaly_detector/
│   └── behavior_analyzer/
└── brainjs/
    ├── pattern_recognizer.json
    └── sequence_predictor.json
```

## Troubleshooting

### "TensorFlow not available" Warning

This is normal if TensorFlow C++ library is not installed. The engine will function in stub mode.

**Solution**: Install TensorFlow and rebuild with `-DENABLE_TENSORFLOW=ON`

### "V8 JavaScript engine not available" Warning

Brain.js features require V8 engine.

**Solution**: Install libv8-dev and rebuild with `-DENABLE_BRAINJS=ON`

### GPU Not Detected

Check CUDA/ROCm installation and rebuild with appropriate flags.

### Model Loading Fails

- Verify model path exists
- Check model format (SavedModel for TensorFlow)
- Ensure sufficient memory

## Advanced Topics

### Custom Model Training

See `docs/MODEL_TRAINING.md` for detailed guide on training custom models.

### Hardware Acceleration

See `docs/HARDWARE_ACCELERATION.md` for GPU setup instructions.

### Model Quantization

TensorFlow models support INT8 and FP16 quantization for improved performance:

```cpp
config.use_quantization = true;  // Enable INT8 quantization
config.use_mixed_precision = true; // Enable mixed precision (FP16/FP32)
```

## API Reference

Complete API documentation available at:
- `include/ai/ai_ml_engine.h`
- `include/ai/tensorflow_backend.h`
- `include/ai/brainjs_backend.h`
- `include/ai/extended_thinking.h`

## License

Copyright (C) 2025 Lackadaisical Security
