#ifndef LAUNCHER_HPP
#define LAUNCHER_HPP

#include <string>
#include <mutex>
#include <functional>
#include <queue>
#include <atomic>

namespace launcher
{

struct Profile
{
  std::string_view username;
  std::string_view character_name;
  std::string_view guild;
  std::string_view token;

  uint64_t level;
  uint64_t last_login;
};

enum class State
{
  DOWNLOADING, PATCHING, NONE
};

struct Progress
{
  int progressPrimary;
  int progressSecondary;

  std::string fileName;
  State state;
};

class Launcher
{
public:
  Launcher();
  ~Launcher();

  [[nodiscard]] Profile profile() const;

  [[nodiscard]] int countToDownload() const;
  [[nodiscard]] int countToPatch() const;

  [[nodiscard]] bool isAuthenticated() const;
  [[nodiscard]] bool isUpdatePaused() const;
  [[nodiscard]] bool isUpdateStopped() const;

  [[nodiscard]] Progress getProgress() const;

  /*
   * Sets _updatePaused to v.
   * This will stop or resume any workers (file check, file update).
   */
  void setUpdatePaused(bool v);

  /*
   * Sets _shouldStop to true
   * This will stop any active workers (file check, file update).
   */
  void stopUpdate();

  /*
   * Authenticates specified user credentials.
   * Returns true on success, false otherwise
   */
  bool authenticate(std::string const & username, std::string const & password) noexcept;

  /*
   * Logs out the current user.
   */
  void logout() noexcept;

  /*
   * Makes sure game files have correct checksums.
   * Populates _toPatch queue.
   *
   *
   * TODO: docs
   */
  bool checkFiles() noexcept;

  /*
   *
   *
   */
  void update() noexcept;

private:
  std::mutex _mutex;

  // requires _mutex lock
  Profile _profile;

  // requires _mutex lock
  std::queue<std::string> _toPatch;
  std::queue<std::string> _toDownload;

  std::atomic<char*> _fileName        = static_cast<char*>(calloc(255, sizeof(char)));
  std::atomic<State> _state           = State::NONE;
  std::atomic_bool _isAuthenticated   = false;
  std::atomic_bool _shouldStop        = false;
  std::atomic_bool _shouldPause       = false;
  std::atomic_int  _progressSecondary = 0;
  std::atomic_int  _progressPrimary   = 0;
};
}

#endif // LAUNCHER_HPP
