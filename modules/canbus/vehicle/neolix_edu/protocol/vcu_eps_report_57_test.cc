/******************************************************************************
 * Copyright 2020 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#include "modules/canbus/vehicle/neolix_edu/protocol/vcu_eps_report_57.h"

#include "glog/logging.h"

#include "gtest/gtest.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace neolix_edu {

class Vcuepsreport57Test : public ::testing::Test {
 public:
  virtual void SetUp() {}
};

TEST_F(Vcuepsreport57Test, reset) {
  uint8_t data[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  int32_t length = 8;
  ChassisDetail cd;
  Vcuepsreport57 accel_cmd;
  accel_cmd.Parse(data, length, &cd);
  EXPECT_EQ(data[0], 0b00000000);
  EXPECT_EQ(data[1], 0b00000000);
  EXPECT_EQ(data[2], 0b00000000);
  EXPECT_EQ(data[3], 0b00000000);
  EXPECT_EQ(data[4], 0b00000000);
  EXPECT_EQ(data[5], 0b00000000);
  EXPECT_EQ(data[6], 0b00000000);
  EXPECT_EQ(data[7], 0b00000000);

  EXPECT_EQ(cd.neolix_edu().vcu_eps_report_57().drive_enable_resp(), false);
  EXPECT_EQ(cd.neolix_edu().vcu_eps_report_57().control_mode_resp(), 0);
  EXPECT_EQ(cd.neolix_edu().vcu_eps_report_57().vcu_eps_report(), false);
  EXPECT_EQ(cd.neolix_edu().vcu_eps_report_57().vcu_real_angle(), 2048);
  EXPECT_EQ(cd.neolix_edu().vcu_eps_report_57().vcu_real_angle_valid(), false);
  EXPECT_EQ(cd.neolix_edu().vcu_eps_report_57().vcu_target_angle_valid(),
            false);
  EXPECT_EQ(cd.neolix_edu().vcu_eps_report_57().vcu_target_angle(), -512);
}

}  // namespace neolix_edu
}  // namespace canbus
}  // namespace apollo
