# API Endpoint Documentation

_Use this template to describe a specific API endpoint. Copy and fill out per endpoint._

## Endpoint

`[HTTP METHOD] /path/to/endpoint`

## Description

_What does this endpoint do?_

## Request

### Parameters

| Name     | In   | Type   | Required | Description         |
|----------|------|--------|----------|---------------------|
| example  | body | string | true     | Example parameter   |

### Request Body (if applicable)

```json
{
  "example": "value"
}
```

## Response

### Success (200)

```json
{
  "result": "success"
}
```

### Error Responses

| Status | Description      |
|--------|------------------|
| 400    | Bad request      |
| 401    | Unauthorized     |
| ...    | ...              |

## Notes

- Authentication required? [Yes/No]
- Permissions/roles needed: [role1, role2]

---

_Last updated: 2025-06-09_
