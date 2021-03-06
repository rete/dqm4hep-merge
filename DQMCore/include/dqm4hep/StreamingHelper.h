/// \file StreamingHelper.h
/*
 *
 * StreamingHelper.h header template automatically generated by a class generator
 * Creation date : lun. ao�t 17 2015
 *
 * This file is part of DQM4HEP libraries.
 *
 * DQM4HEP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * based upon these libraries are permitted. Any copy of these libraries
 * must include this copyright notice.
 *
 * DQM4HEP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with DQM4HEP.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @author Remi Ete
 * @copyright CNRS , IPNL
 */

#ifndef DQM4HEP_STREAMINGHELPER_H
#define DQM4HEP_STREAMINGHELPER_H

// -- dqm4hep headers
#include <dqm4hep/Internal.h>
#include <dqm4hep/StatusCodes.h>

// -- xdrstream headers
#include <xdrstream/xdrstream.h>

namespace dqm4hep {

  namespace core {

    class StreamingHelper {
    public:
      /**
       */
      template <typename T>
      static xdrstream::Status read(xdrstream::IODevice *pDevice, T &stlContainer);

      /**
       */
      template <typename T>
      static xdrstream::Status write(xdrstream::IODevice *pDevice, const T &stlContainer);

      /**
       */
      template <typename KeyType, typename ValueType>
      static xdrstream::Status read(xdrstream::IODevice *pDevice, std::map<KeyType, ValueType> &stlContainer);

      /**
       */
      template <typename KeyType, typename ValueType>
      static xdrstream::Status write(xdrstream::IODevice *pDevice, const std::map<KeyType, ValueType> &stlContainer);

      /**
       */
      template <typename KeyType, typename VectorType>
      static xdrstream::Status read(xdrstream::IODevice *pDevice,
                                    std::map<KeyType, std::vector<VectorType>> &stlContainer);

      /**
       */
      template <typename KeyType, typename VectorType>
      static xdrstream::Status write(xdrstream::IODevice *pDevice,
                                     const std::map<KeyType, std::vector<VectorType>> &stlContainer);

      /**
       */
      template <typename KeyType, typename ValueType>
      static xdrstream::Status read(xdrstream::IODevice *pDevice, std::multimap<KeyType, ValueType> &stlContainer);

      /**
       */
      template <typename KeyType, typename ValueType>
      static xdrstream::Status write(xdrstream::IODevice *pDevice,
                                     const std::multimap<KeyType, ValueType> &stlContainer);

      /**
       */
      template <typename T>
      static xdrstream::Status readStreamables(xdrstream::IODevice *pDevice, T &stlContainer);

      /**
       */
      template <typename T>
      static xdrstream::Status writeStreamables(xdrstream::IODevice *pDevice, const T &stlContainer);

      /**
       */
      template <typename KeyType, typename ValueType>
      static xdrstream::Status readStreamables(xdrstream::IODevice *pDevice,
                                               std::map<KeyType, ValueType> &stlContainer);

      /**
       */
      template <typename KeyType, typename ValueType>
      static xdrstream::Status writeStreamables(xdrstream::IODevice *pDevice,
                                                const std::map<KeyType, ValueType> &stlContainer);

      /**
       */
      template <typename KeyType, typename ValueType>
      static xdrstream::Status readStreamables(xdrstream::IODevice *pDevice,
                                               std::multimap<KeyType, ValueType> &stlContainer);

      /**
       */
      template <typename KeyType, typename ValueType>
      static xdrstream::Status writeStreamables(xdrstream::IODevice *pDevice,
                                                const std::multimap<KeyType, ValueType> &stlContainer);
    };

    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------

    template <typename T>
    inline xdrstream::Status StreamingHelper::read(xdrstream::IODevice *pDevice, T &stlContainer) {
      uint32_t nRead = 0;
      XDR_STREAM(pDevice->read(&nRead))

      for (uint32_t i = 0; i < nRead; i++) {
        typename T::value_type value;
        XDR_STREAM(pDevice->read(&value))
        stlContainer.insert(stlContainer.end(), value);
      }

      return xdrstream::XDR_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    template <typename T>
    inline xdrstream::Status StreamingHelper::write(xdrstream::IODevice *pDevice, const T &stlContainer) {
      uint32_t nWrite = stlContainer.size();
      XDR_STREAM(pDevice->write(&nWrite))

      for (auto iter = stlContainer.begin(), endIter = stlContainer.end(); endIter != iter; ++iter)
        XDR_STREAM(pDevice->write(&(*iter)))

      return xdrstream::XDR_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    template <typename KeyType, typename ValueType>
    inline xdrstream::Status StreamingHelper::read(xdrstream::IODevice *pDevice,
                                                   std::map<KeyType, ValueType> &stlContainer) {
      uint32_t nRead = 0;
      XDR_STREAM(pDevice->read(&nRead))

      for (uint32_t i = 0; i < nRead; i++) {
        KeyType key;
        ValueType value;

        XDR_STREAM(pDevice->read(&key))
        XDR_STREAM(pDevice->read(&value))

        stlContainer.insert(stlContainer.end(), typename std::map<KeyType, ValueType>::value_type(key, value));
      }

      return xdrstream::XDR_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    template <typename KeyType, typename ValueType>
    inline xdrstream::Status StreamingHelper::write(xdrstream::IODevice *pDevice,
                                                    const std::map<KeyType, ValueType> &stlContainer) {
      uint32_t nWrite = stlContainer.size();
      XDR_STREAM(pDevice->write(&nWrite))

      for (auto iter = stlContainer.begin(), endIter = stlContainer.end(); endIter != iter; ++iter) {
        XDR_STREAM(pDevice->write(&(iter->first)))
        XDR_STREAM(pDevice->write(&(iter->second)))
      }

      return xdrstream::XDR_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    template <typename KeyType, typename VectorType>
    inline xdrstream::Status StreamingHelper::read(xdrstream::IODevice *pDevice,
                                                   std::map<KeyType, std::vector<VectorType>> &stlContainer) {
      uint32_t nRead = 0;
      XDR_STREAM(pDevice->read(&nRead))

      for (uint32_t i = 0; i < nRead; i++) {
        KeyType key;
        std::vector<VectorType> value;

        XDR_STREAM(pDevice->read(&key))
        XDR_STREAM(StreamingHelper::read(pDevice, value))

        stlContainer.insert(stlContainer.end(),
                            typename std::map<KeyType, std::vector<VectorType>>::value_type(key, value));
      }

      return xdrstream::XDR_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    template <typename KeyType, typename VectorType>
    inline xdrstream::Status StreamingHelper::write(xdrstream::IODevice *pDevice,
                                                    const std::map<KeyType, std::vector<VectorType>> &stlContainer) {
      uint32_t nWrite = stlContainer.size();
      XDR_STREAM(pDevice->write(&nWrite))

      for (auto iter = stlContainer.begin(), endIter = stlContainer.end(); endIter != iter; ++iter) {
        XDR_STREAM(pDevice->write(&(iter->first)))
        XDR_STREAM(StreamingHelper::write(pDevice, iter->second))
      }

      return xdrstream::XDR_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    template <typename KeyType, typename ValueType>
    inline xdrstream::Status StreamingHelper::read(xdrstream::IODevice *pDevice,
                                                   std::multimap<KeyType, ValueType> &stlContainer) {
      uint32_t nRead = 0;
      XDR_STREAM(pDevice->read(&nRead))

      for (uint32_t i = 0; i < nRead; i++) {
        KeyType key;
        ValueType value;

        XDR_STREAM(pDevice->read(&key))
        XDR_STREAM(pDevice->read(&value))

        stlContainer.insert(stlContainer.end(), typename std::multimap<KeyType, ValueType>::value_type(key, value));
      }

      return xdrstream::XDR_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    template <typename KeyType, typename ValueType>
    inline xdrstream::Status StreamingHelper::write(xdrstream::IODevice *pDevice,
                                                    const std::multimap<KeyType, ValueType> &stlContainer) {
      uint32_t nWrite = stlContainer.size();
      XDR_STREAM(pDevice->write(&nWrite))

      for (typename std::multimap<KeyType, ValueType>::const_iterator iter = stlContainer.begin(),
                                                                      endIter = stlContainer.end();
           endIter != iter; ++iter) {
        XDR_STREAM(pDevice->write(&(iter->first)))
        XDR_STREAM(pDevice->write(&(iter->second)))
      }

      return xdrstream::XDR_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    template <typename T>
    inline xdrstream::Status StreamingHelper::readStreamables(xdrstream::IODevice *pDevice, T &stlContainer) {
      uint32_t nRead = 0;
      XDR_STREAM(pDevice->read(&nRead))

      for (uint32_t i = 0; i < nRead; i++) {
        auto pObject = new T();
        XDR_STREAM(pObject->stream(xdrstream::XDR_READ_STREAM, pDevice))
        stlContainer.insert(stlContainer.end(), pObject);
      }

      return xdrstream::XDR_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    template <typename T>
    inline xdrstream::Status StreamingHelper::writeStreamables(xdrstream::IODevice *pDevice, const T &stlContainer) {
      uint32_t nWrite = stlContainer.size();
      XDR_STREAM(pDevice->write(&nWrite))

      for (typename T::const_iterator iter = stlContainer.begin(), endIter = stlContainer.end(); endIter != iter;
           ++iter)
        XDR_STREAM((*iter)->stream(xdrstream::XDR_WRITE_STREAM, pDevice))

      return xdrstream::XDR_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    template <typename KeyType, typename ValueType>
    inline xdrstream::Status StreamingHelper::readStreamables(xdrstream::IODevice *pDevice,
                                                              std::map<KeyType, ValueType> &stlContainer) {
      uint32_t nRead = 0;
      XDR_STREAM(pDevice->read(&nRead))

      for (uint32_t i = 0; i < nRead; i++) {
        KeyType key;
        XDR_STREAM(pDevice->read(&key))

        auto pObject = new ValueType();
        XDR_STREAM(pObject->stream(xdrstream::XDR_READ_STREAM, pDevice))

        typename std::map<KeyType, ValueType>::value_type value(key, pObject);
        stlContainer.insert(stlContainer.end(), value);
      }

      return xdrstream::XDR_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    template <typename KeyType, typename ValueType>
    inline xdrstream::Status StreamingHelper::writeStreamables(xdrstream::IODevice *pDevice,
                                                               const std::map<KeyType, ValueType> &stlContainer) {
      uint32_t nWrite = stlContainer.size();
      XDR_STREAM(pDevice->write(&nWrite))

      for (typename std::map<KeyType, ValueType>::const_iterator iter = stlContainer.begin(),
                                                                 endIter = stlContainer.end();
           endIter != iter; ++iter) {
        XDR_STREAM(pDevice->write(&(iter->first)))
        XDR_STREAM((iter->second)->stream(xdrstream::XDR_WRITE_STREAM, pDevice))
      }

      return xdrstream::XDR_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    template <typename KeyType, typename ValueType>
    inline xdrstream::Status StreamingHelper::readStreamables(xdrstream::IODevice *pDevice,
                                                              std::multimap<KeyType, ValueType> &stlContainer) {
      uint32_t nRead = 0;
      XDR_STREAM(pDevice->read(&nRead))

      for (uint32_t i = 0; i < nRead; i++) {
        KeyType key;
        XDR_STREAM(pDevice->read(&key))

        auto pObject = new ValueType();
        XDR_STREAM(pObject->stream(xdrstream::XDR_READ_STREAM, pDevice))

        typename std::multimap<KeyType, ValueType>::value_type value(key, pObject);
        stlContainer.insert(stlContainer.end(), value);
      }

      return xdrstream::XDR_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    template <typename KeyType, typename ValueType>
    inline xdrstream::Status StreamingHelper::writeStreamables(xdrstream::IODevice *pDevice,
                                                               const std::multimap<KeyType, ValueType> &stlContainer) {
      uint32_t nWrite = stlContainer.size();
      XDR_STREAM(pDevice->write(&nWrite))

      for (typename std::multimap<KeyType, ValueType>::const_iterator iter = stlContainer.begin(),
                                                                      endIter = stlContainer.end();
           endIter != iter; ++iter) {
        XDR_STREAM(pDevice->write(&(iter->first)))
        XDR_STREAM((iter->second)->stream(xdrstream::XDR_WRITE_STREAM, pDevice))
      }

      return xdrstream::XDR_SUCCESS;
    }
  }
}

#endif //  DQM4HEP_STREAMINGHELPER_H
