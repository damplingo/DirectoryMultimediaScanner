#include "THttpHandler.h"

#include <fmt/format.h>
#include <userver/server/handlers/http_handler_base.hpp>
#include <string>
#include <string_view>
#include <vector>
#include <optional>

std::shared_ptr<TDirectoryScaner> THttpHandler::scanner_ = nullptr;
THttpHandler::THttpHandler(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : HttpHandlerBase(config, context) {
}

std::string THttpHandler::HandleRequestThrow(
    const userver::server::http::HttpRequest& request,
    userver::server::request::RequestContext& context) const {
    
    // Устанавливаем тип контента
    request.GetHttpResponse().SetContentType(
        userver::http::content_type::kApplicationJson);
    
    // Получаем актуальный отчёт от сканера
    nlohmann::json report = scanner_->GetLatestReport();
    
    // Преобразуем в строку и возвращаем
    return report.dump(4);  // 4 пробела для форматирования
}
void THttpHandler::SetScanner(std::shared_ptr<TDirectoryScaner> scanner) {
    scanner_ = std::move(scanner);
}
void NHttpHandler::AppendHandler(userver::components::ComponentList& componentList) {
    componentList.Append<THttpHandler>();
}