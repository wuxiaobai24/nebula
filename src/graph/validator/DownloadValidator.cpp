/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#include "graph/validator/DownloadValidator.h"

#include "graph/planner/plan/Admin.h"
#include "parser/MutateSentences.h"

namespace nebula {
namespace graph {

// Plan to download SST file from HDFS
Status DownloadValidator::toPlan() {
  auto sentence = static_cast<DownloadSentence *>(sentence_);
  if (sentence->host() == nullptr || sentence->port() == 0 || sentence->path() == nullptr) {
    return Status::SemanticError(
        "HDFS path illegal."
        "Should be HDFS://${HDFS_HOST}:${HDFS_PORT}/${HDFS_PATH}");
  }
  auto *doNode =
      Download::make(qctx_, nullptr, *sentence->host(), sentence->port(), *sentence->path());
  root_ = doNode;
  tail_ = root_;
  return Status::OK();
}

}  // namespace graph
}  // namespace nebula
