/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include "bat/ads/internal/ml/data/text_data.h"
#include "bat/ads/internal/ml/data/vector_data.h"
#include "bat/ads/internal/ml/transformation/hash_vectorizer.h"
#include "bat/ads/internal/ml/transformation/hashed_ngrams.h"

namespace ads {
namespace ml {
namespace transformation {

HashedNGrams::HashedNGrams()
    : Transformation(TransformationType::HASHED_NGRAMS) {
  hash_vectorizer = std::make_unique<HashVectorizer>(HashVectorizer());
}

HashedNGrams::HashedNGrams(const HashedNGrams& hashed_ngrams)
    : Transformation(TransformationType::HASHED_NGRAMS) {
  HashVectorizer hash_vectorizer_copy = *(hashed_ngrams.hash_vectorizer);
  hash_vectorizer = std::make_unique<HashVectorizer>(hash_vectorizer_copy);
}

HashedNGrams::~HashedNGrams() = default;

HashedNGrams::HashedNGrams(int bucket_count, const std::vector<int>& subgrams)
    : Transformation(TransformationType::HASHED_NGRAMS) {
  hash_vectorizer =
      std::make_unique<HashVectorizer>(HashVectorizer(bucket_count, subgrams));
}

std::unique_ptr<data::Data> HashedNGrams::Apply(
    const std::unique_ptr<data::Data>& input_data) {
  if (input_data->GetType() != data::DataType::TEXT_DATA) {
    return std::make_unique<data::Data>(
        data::VectorData(0, std::map<unsigned, double>()));
  }

  data::TextData* text_data = static_cast<data::TextData*>(input_data.get());

  std::map<unsigned, double> frequences =
      hash_vectorizer->GetFrequencies(text_data->GetText());
  int dimension_count = hash_vectorizer->GetBucketCount();

  return std::make_unique<data::VectorData>(
      data::VectorData(dimension_count, frequences));
}

}  // namespace transformation
}  // namespace ml
}  // namespace ads
