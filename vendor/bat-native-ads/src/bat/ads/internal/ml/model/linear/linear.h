/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BAT_ADS_INTERNAL_ML_MODEL_LINEAR_LINEAR_H_
#define BAT_ADS_INTERNAL_ML_MODEL_LINEAR_LINEAR_H_

#include <map>
#include <string>

#include "bat/ads/internal/ml/data/data.h"
#include "bat/ads/internal/ml/data/vector_data.h"
#include "bat/ads/internal/ml/ml_aliases.h"

namespace ads {
namespace ml {
namespace model {

class Linear {
 public:
  Linear();

  Linear(const Linear& other);

  explicit Linear(const std::string& model);

  Linear(const std::map<std::string, data::VectorData>& weights,
         const std::map<std::string, double>& biases);

  ~Linear();

  PredictionMap Predict(const data::VectorData& x);

  PredictionMap TopPredictions(const data::VectorData& x, int top_count = -1);

 private:
  std::map<std::string, data::VectorData> weights_;
  std::map<std::string, double> biases_;
};

}  // namespace model
}  // namespace ml
}  // namespace ads

#endif  // BAT_ADS_INTERNAL_ML_MODEL_LINEAR_LINEAR_H_
