// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*!
 * @file UnderlayMessageTypes.cpp
 * This header file contains the implementation of the serialization functions.
 *
 * This file was generated by the tool fastcdrgen.
 */

#include "cyber/transport/rtps/underlay_message_type.h"

#include "fastcdr/Cdr.h"
#include "fastcdr/FastBuffer.h"

#include "cyber/common/log.h"

namespace apollo {
namespace cyber {
namespace transport {

UnderlayMessageType::UnderlayMessageType() {
  setName("UnderlayMessage");
  m_typeSize = (uint32_t)UnderlayMessage::getMaxCdrSerializedSize() +
               4 /*encapsulation*/;
  m_isGetKeyDefined = UnderlayMessage::isKeyDefined();
  m_keyBuffer =
      (unsigned char*)malloc(UnderlayMessage::getKeyMaxCdrSerializedSize() > 16
                                 ? UnderlayMessage::getKeyMaxCdrSerializedSize()
                                 : 16);
}

UnderlayMessageType::~UnderlayMessageType() {
  if (m_keyBuffer != nullptr) {
    free(m_keyBuffer);
  }
}

bool UnderlayMessageType::serialize(void* data, SerializedPayload_t* payload) {
  UnderlayMessage* p_type = reinterpret_cast<UnderlayMessage*>(data);
  eprosima::fastcdr::FastBuffer fastbuffer(
      reinterpret_cast<char*>(payload->data),
      payload->max_size);  // Object that manages the raw buffer.
  eprosima::fastcdr::Cdr ser(
      fastbuffer, eprosima::fastcdr::Cdr::DEFAULT_ENDIAN,
      eprosima::fastcdr::Cdr::DDS_CDR);  // Object that serializes the data.
  payload->encapsulation =
      ser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE
                                                                 : CDR_LE;
  // Serialize encapsulation
  ser.serialize_encapsulation();
  p_type->serialize(ser);  // Serialize the object:
  payload->length =
      (uint32_t)ser.getSerializedDataLength();  // Get the serialized length
  return true;
}

bool UnderlayMessageType::deserialize(SerializedPayload_t* payload,
                                      void* data) {
  UnderlayMessage* p_type = reinterpret_cast<UnderlayMessage*>(
      data);  // Convert DATA to pointer of your type
  eprosima::fastcdr::FastBuffer fastbuffer(
      reinterpret_cast<char*>(payload->data),
      payload->length);  // Object that manages the raw buffer.
  eprosima::fastcdr::Cdr deser(
      fastbuffer, eprosima::fastcdr::Cdr::DEFAULT_ENDIAN,
      eprosima::fastcdr::Cdr::DDS_CDR);  // Object that deserializes the data.
  // Deserialize encapsulation.
  deser.read_encapsulation();
  payload->encapsulation =
      deser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE
                                                                   : CDR_LE;
  p_type->deserialize(deser);  // Deserialize the object:
  return true;
}

std::function<uint32_t()> UnderlayMessageType::getSerializedSizeProvider(
    void* data) {
  return [data]() -> uint32_t {
    return (uint32_t)type::getCdrSerializedSize(
               *static_cast<UnderlayMessage*>(data)) +
           4 /*encapsulation*/;
  };
}

void* UnderlayMessageType::createData() {
  return reinterpret_cast<void*>(new UnderlayMessage());
}

void UnderlayMessageType::deleteData(void* data) {
  delete (reinterpret_cast<UnderlayMessage*>(data));
}

bool UnderlayMessageType::getKey(void* data, InstanceHandle_t* handle) {
  RETURN_VAL_IF((!m_isGetKeyDefined), false);
  UnderlayMessage* p_type = reinterpret_cast<UnderlayMessage*>(data);
  eprosima::fastcdr::FastBuffer fastbuffer(
      reinterpret_cast<char*>(m_keyBuffer),
      UnderlayMessage::getKeyMaxCdrSerializedSize());  // Object that manages
                                                       // the raw buffer.
  eprosima::fastcdr::Cdr ser(
      fastbuffer, eprosima::fastcdr::Cdr::BIG_ENDIANNESS);  // Object that
                                                            // serializes the
                                                            // data.
  p_type->serializeKey(ser);
  if (UnderlayMessage::getKeyMaxCdrSerializedSize() > 16) {
    m_md5.init();
    m_md5.update(m_keyBuffer, (unsigned int)ser.getSerializedDataLength());
    m_md5.finalize();
    for (uint8_t i = 0; i < 16; ++i) {
      handle->value[i] = m_md5.digest[i];
    }
  } else {
    for (uint8_t i = 0; i < 16; ++i) {
      handle->value[i] = m_keyBuffer[i];
    }
  }
  return true;
}

}  // namespace transport
}  // namespace cyber
}  // namespace apollo
